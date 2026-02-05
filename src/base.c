#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//#include <proj.h>

#define PI 3.1415926535897931
#define c 299792458.0

/* NOTE: -X is westing, +X is easting, -Y is southing, +Y is northing */
enum Dimension{X, Y, Z};

typedef enum BaseModel BaseModel;
enum BaseModel{FSPL, LOG_DISTANCE, ALPHA_BETA};

/* For vertical/horizontal antenna patterns */
typedef double VPat[181];
typedef double HPat[360];

/* Point slots can be accesed with point[X], point[Y], point[Z] */
typedef double Point[3];

typedef struct Tx Tx;
struct Tx{
	Point pos;     /* Tx coordinates projected to EPSG:3857, Z coordinate is height in meters  */
	double azimuth;   /* angle relative to true north in degrees  */
	double downtilt;  /* angle relative to the horizon in degrees */
	double freq;      /* carrier frequency in Hz */
	double power;     /* Tx power in dBm */
	double gain;      /* isotropic antenna gain in dB */
};

/* Use the PROJ library to project the coordinates from EPSG:4326 (lon,lat) to EPSG:3857 (x,y)
 * The library can be installed with `conda install -c conda-forge proj'
 * https://proj.org/en/stable/development/quickstart.html
 * The Z coordinate will not be affected and can be left as is
 * Overwrite the current value of `coord' */
void
project_coord(Point coord);

/* Read the topology from a CSV file, assume each column is seperated only by 1 comma
 * CSV will have the following format:
 * lon,lat,azimuth,downtilt,height,freq,power,gain
 * Note that lon/lat will be provided in EPSG:4326 and must be projected to EPSG:3857
 * Note that frequency will be provided in MHz, and must be converted to Hz
 * You must allocate a buffer large enough to hold a Tx for each line of the CSV
 * Read a line into each row of the buffer, the patterns can be left blank
 * Set the value at `len' equal to the number of lines read
 * Return the freshly allocated/populated buffer
 * If the file could not be opened or there was a parsing error, return NULL */
Tx *
read_topology(char *path, int *len);

/* NOTES:
 * - From here on it is assumed that all coordinates are projected to EPSG:3857
 * - A flat earth approximation can be used for all projected coordinates */

/* Read vertical and horizontal radiation patterns from the file at `path'
 * Return 0 if the file couldn't be read, 1 otherwise
 * The first 360 lines of the file define horizontal pattern
 * Line 1 will define the gain for zero degrees, line 2 for 1 degree and so on...
 * This continues until the first 360 entries are read
 * The remaining 181 lines define vertical gain in the same manner
 * Line 361 will define the gain for -90 degrees, line 362 for -89 degrees and so on... */
char
read_pattern(char *path, VPat *vertical, HPat *horizontal);

/* Return the azimuth in degrees of the ray that passes through both points
 * This angle should be wrapped to be between 0 and 360 degrees */
double
relative_azimuth(Point tx, Point rx);

/* Return the angle in degrees relative to the horizon of the line that points from Tx to Rx
 * If this line points towards the ground, this angle will be negative
 * This angle should be wrapped to be between -90 and +90 degrees */
double
relative_downtilt(Point tx, Point rx);

/* Convert dBm to Watts and return the result */
double dbm_to_watts(double dbm) {
    double result = pow(10, (dbm/10));
    result = result / 1000;
    return result;
}

/* Convert Watts to dBm and return the result */
double watts_to_dbm(double watts) {
    double result = 10 * log10(watts) + 30;
    return result;
}

/* Calculate total antenna gain as seen from coordinate (X,Y,Z) `pos'
 * First find the azimuth between the Tx and the coordinate
 * Subtract the Tx azimuth from this newly found azimuth angle to find the effective azimuth
 * Calculate the vertical angle between between the top of the antenna, and the coordinate
 * Subtract the Tx downtilt from this to find the effective downtilt
 * Effective azimuth should be wrapped so that it is between 0 and 360
 * Effective downtilt should be wrapped so that it is between -90 and 90
 * Find the nearest angle to the effective azimuth in the horizontal pattern and store associated gain
 * Find the nearest angle to the effective downtilt in the vertical pattern and store associated gain
 * See the specs for `read_pattern' for details on how antenna patterns are stored
 * Convert both vertical and horizontal gains to Watts and take their magnitude
 * Convert this magnitude back to dBm, and add it to the Tx isotropic gain
 * Return this value as the total antenna gain */
double
antenna_gain(Tx *tx, VPat vertical, HPat horizontal, Point pos);

/* Return the freespace path loss over the given distance
 * Relevant transmission parameters will be supplied in `tx'
 * See equation 3 in this paper https://ieeexplore.ieee.org/document/7504435 */
double fspl(Tx *tx, double distance)
{
    if (tx == NULL){
        return -INFINITY;
    }
    double result = 0;
    double f = tx-> freq;
    if (f <= 0 || distance < 0) {
        return -INFINITY;
    }
    result = 20 * log10((4* PI * distance * f)/c);
    return result;
}
/* Return the log distance path loss over the given distance with parameter/exponent `n'
 * Do not include Gaussian noise
 * Relevant transmission parameters will be supplied in `tx'
 * See equation 2 in this paper https://ieeexplore.ieee.org/document/7504435 */

// ALVI RASHID
double log_distance(Tx *tx, double distance, double n)
{
    if (tx == NULL) {
        return -INFINITY;
    }
    if (distance <= 0 || n <= 0) {
        return -INFINITY;
    }
    const double d = 1.0;
    double L = fspl(tx, d);
    double Ld = L + 10.0 * n * log10(distance);
    return Ld;
}

/* Return the alpha-beta path loss over the given distance with the given parameters
 * Do not include Gaussian noise
 * Relevant transmission parameters will be supplied in `tx'
 * See equation 1 in this paper https://ieeexplore.ieee.org/document/7504435 */
//ALVI RASHID
double alpha_beta(Tx *tx, double distance, double alpha, double beta)
{
    if (tx == NULL) {
        return -INFINITY;
    }
    if (distance <= 0.0 || tx->freq <= 0.0) {
        return -INFINITY;
    }

    const double f_ghz = tx->freq / 1e9;

    return 10.0 * alpha * log10(distance/1) + beta + 10.0 * log10(f_ghz);
}

/* Compute the total given the Tx, antenna pattern, Rx, and chosen propagation model
 * Assume `params' is already allocated and contains the expected number of elements
 * For FSPL, params can be NULL
 * For log-distance, params will contain the parameter `n'
 * For alpha-beta, params will be an array of length 2 with format {alpha, beta}
 * The total loss = antenna gain + chosen model loss (FSPL, log-distance, alpha-beta) */
double
base_loss(Tx *tx, VPat vertical, HPat horizontal, Point rx, double *params, BaseModel model);

// int main(int argc, char **argv)
// {
// 	int topology_cnt;
// 	VPat vertical[181];
//         HPat horizontal[360];
// 	//VPat HPathorizontal[365];
// 	Tx *tx;
// 	if(argc < 2){
// 		fprintf(stderr, "usage: ./gprop <topology> <pattern>\n");
// 		return 0;
// 	}
// 	tx = read_topology(argv[1], &topology_cnt);
// 	if(tx == NULL){
// 		fprintf(stderr, "failed to read topology\n");
// 		return 1;
// 	}
// 	if(!read_pattern(argv[2], vertical, horizontal)){
// 		fprintf(stderr, "failed to read antenna pattern\n");
// 		free(tx);
// 		return 1;
// 	}
// 	printf("success\n");
// 	free(tx);
// 	return 0;
// }


