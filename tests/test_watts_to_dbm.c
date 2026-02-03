#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "../src/base.h"

int main (int argc, char **argv) {

    // Test 1
    double result = watts_to_dbm(0.01);
    double expected = 10;
    printf("\n");
    printf("Test 1 [0.01W]: Expected: %f dBm\nActual: %f dBm\n", expected, result);
    if (fabs(result - expected) < 0.0001) {
        puts("passed\n");
    }
    else {
        puts("failed test 1");
    }

    // Test 2
    result = watts_to_dbm(2511.8864);
    expected = 64;
    printf("Test 2 [2511.8864W]: Expected: %f dBm\nActual: %f dBm\n", expected, result);
    if (fabs(result - expected) < 0.0001) {
        puts("passed");
    }
    else {
        puts("failed test 2");
    }

    // Test 3 (large number test)
    result = watts_to_dbm(pow(10, 96.9));
    expected = 999;
    printf("\nTest 3 [~7.94e96W]: Expected: %f dBm\nActual: %f dBm\n", expected, result);
    if (fabs(result - expected) < 0.001) puts("passed");
    else puts("failed test 3");

    // Test 4
    result = watts_to_dbm(0.001);
    expected = 0;
    printf("\nTest 4 [0.001W]: Expected: %f dBm\nActual: %f dBm\n", expected, result);
    if (fabs(result - expected) < 0.0001) puts("passed");
    else puts("failed test 4");

    // Test 5
    result = watts_to_dbm(0.000001);
    expected = -30;
    printf("\nTest 5 [1e-6W]: Expected: %f dBm\nActual: %f dBm\n", expected, result);
    if (fabs(result - expected) < 0.0001) puts("passed");
    else puts("failed test 5");

    // Test 6
    result = watts_to_dbm(pow(10, (3.5 - 30) / 10));
    expected = 3.5;
    printf("\nTest 6 [~0.00224W]: Expected: %f dBm\nActual: %f dBm\n", expected, result);
    if (fabs(result - expected) < 0.0001) puts("passed");
    else puts("failed test 6");

    // Test 7
    result = watts_to_dbm(pow(10, (-5.7 - 30) / 10));
    expected = -5.7;
    printf("\nTest 7 [~0.00027W]: Expected: %f dBm\nActual: %f dBm\n", expected, result);
    if (fabs(result - expected) < 0.0001) puts("passed");
    else puts("failed test 7");

    return 0;
}
