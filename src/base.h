#ifndef BASE_H
#define BASE_H



typedef double Point[3];
typedef struct Tx Tx;
struct Tx {
 Point pos;     /* Tx coordinates projected to EPSG:3857, Z coordinate is height in meters  */
 double azimuth;   /* angle relative to true north in degrees  */
 double downtilt;  /* angle relative to the horizon in degrees */
 double freq;      /* carrier frequency in Hz */
 double power;     /* Tx power in dBm */
 double gain;      /* isotropic antenna gain in dB */
  };

double dbm_to_watts(double dbm);
double watts_to_dbm(double watts);
double fspl(Tx *tx, double distance);
double log_distance(Tx *tx, double distance, double n);


#endif
