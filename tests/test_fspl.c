#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "../src/base.h"

int main (int argc, char **argv) {
    Tx tx;
    double result;
    double expected;
    printf("\n");
    //Test 1
    tx.freq = 2.4e9; //GHz
    result = fspl(&tx, 1.0);
    expected = 40.05;
    printf("Test 1 [2.4Ghz, 1.0m]: Expected: %f dB\nActual: %f dB\n", expected, result);
    if (fabs(result - expected) < 0.01) {
        puts("passed\n");
    }
    else {
        puts("failed test 1");
    }

    //Test 2
    tx.freq = 1.0e6; //MHz
    result = fspl(&tx, 12.4);
    expected = -5.68;
    printf("Test 2 [1.0MHz, 12.4m]: Expected: %f dB\nActual: %f dB\n", expected, result);
    if (fabs(result - expected) < 0.01) {
        puts("passed\n");
    }
    else {
        puts("failed test 2");
    }

    //Test 3
    tx.freq = -999;
    result = fspl(&tx, -23.4823);
    expected = -INFINITY;
    printf("Test 3[Invalid Inputs Test, -999Hz, -23.48m] \n");
    if (result == expected) {
        puts("passed\n");
    }
    else {
        puts("failed test 3");
    }

    //Test 4
    tx.freq = -0.01;
    result = fspl(&tx, 0.01);
    expected = -INFINITY;
    printf("Test 4[Invalid Inputs Test, -0.01Hz, 0.01m] \n");
    if (result == expected) {
        puts("passed\n");
    }
    else {
        puts("failed test 4");
    }

    //Test 5
    tx.freq = 6.5e3;
    result = fspl(&tx, -0.0001);
    expected = -INFINITY;
    printf("Test 5[Invalid Inputs Test, 6.5KHz, -0.0001m]\n");
    if (result == expected) {
        puts("passed\n");
    }
    else {
        puts("failed test 5");
    }
}
