#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "../src/base.h"

int main(int argc, char **argv) {
    Tx tx;
    double result;
    double expected;

    printf("\n");
    // Test 1
    tx.freq = 2.4e9;
    result = log_distance(&tx, 10.0, 2.0);
    expected = fspl(&tx, 1.0) + 20.0;
    printf("Test 1 [2.4GHz, 10m, n=2]\nExpected: %f dB\nActual: %f dB\n", expected, result);
    if (fabs(result - expected) < 0.01) puts("passed\n");
    else puts("failed test 1\n");

    //Test 2
    tx.freq = 900e6;
    result = log_distance(&tx, 1.0, 3.0);
    expected = fspl(&tx, 1.0);
    printf("Test 2 [900MHz, 1m, n=3]\nExpected: %f dB\nActual: %f dB\n", expected, result);
    if (fabs(result - expected) < 0.01) puts("passed\n");
    else puts("failed test 2\n");

    //Test 3
    tx.freq = 1.0e6;
    result = log_distance(&tx, 0.1, 2.0);
    expected = fspl(&tx, 1.0) - 20.0;
    printf("Test 3 [1MHz, 0.1m, n=2]\nExpected: %f dB\nActual: %f dB\n", expected, result);
    if (fabs(result - expected) < 0.01) puts("passed\n");
    else puts("failed test 3\n");

    //Test 4
    tx.freq = 2.4e9;
    result = log_distance(&tx, -5.0, 2.0);
    expected = -INFINITY;
    printf("Test 4 [Invalid distance]\n");
    if (result == expected) puts("passed\n");
    else puts("failed test 4\n");

    //Test 5
    result = log_distance(NULL, 10.0, 2.0);
    expected = -INFINITY;
    printf("Test 5 [Invalid tx]\n");
    if (result == expected) puts("passed\n");
    else puts("failed test 5\n");
    return 0;

}