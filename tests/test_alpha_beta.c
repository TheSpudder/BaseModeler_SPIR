
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "../src/base.h"

//ALVI RASHID
static int almost_equal(double a, double b, double tol)
{
       return fabs(a - b) < tol;
}

int main(void)
{
    Tx tx;
    double result, expected, L1;
    const double tol = 0.01;

    printf("\n");

    //test 1
    tx.freq = 2.4e9;
    L1 = fspl(&tx, 1.0);
    expected = L1 + 20.0;
    result = alpha_beta(&tx, 10.0, 2.0, 0.0);
    printf("Test 1 [2.4GHz, d=10, a=2.0, b=0]: Expected: %.4f dB\nActual:   %.4f dB\n",expected, result);
    puts(almost_equal(result, expected, tol) ? "passed\n" : "failed\n");

    //test 2
    tx.freq = 2.4e9;
    L1 = fspl(&tx, 1.0);
    expected = L1 + 20.0 + 7.5;
    result = alpha_beta(&tx, 10.0, 2.0, 7.5);
    printf("Test 2 [2.4GHz, d=10, a=2.0, b=7.5]: Expected: %.4f dB\nActual:   %.4f dB\n",
           expected, result);
    puts(almost_equal(result, expected, tol) ? "passed\n" : "failed\n");

    //test 3
    tx.freq = 9.15e8;
    L1 = fspl(&tx, 1.0);
    expected = L1 - 20.0;
    result = alpha_beta(&tx, 0.1, 2.0, 0.0);
    printf("Test 3 [915MHz, d=0.1, a=2.0, b=0]: Expected: %.4f dB\nActual:   %.4f dB\n",
           expected, result);
    puts(almost_equal(result, expected, tol) ? "passed\n" : "failed\n");

   //test 4
    tx.freq = 5.8e9;
    L1 = fspl(&tx, 1.0);
    expected = L1 - 3.0;
    result = alpha_beta(&tx, 123.0, 0.0, -3.0);
    printf("Test 4 [5.8GHz, d=123, a=0.0, b=-3]: Expected: %.4f dB\nActual:   %.4f dB\n",
           expected, result);
    puts(almost_equal(result, expected, tol) ? "passed\n" : "failed\n");

   //test5
    tx.freq = 2.4e9;
    result = alpha_beta(NULL, 10.0, 2.0, 0.0);
    printf("Test 5 [tx=NULL]: Expected: -INFINITY\nActual:   %f\n", result);
       //test 6
    puts(isinf(result) && result < 0 ? "passed\n" : "failed\n");
    result = alpha_beta(&tx, 0.0, 2.0, 0.0);
    printf("Test 6 [d=0]: Expected: -INFINITY\nActual:   %f\n", result);
       // test 7
    puts(isinf(result) && result < 0 ? "passed\n" : "failed\n");
    result = alpha_beta(&tx, 10.0, -1.0, 0.0);
    printf("Test 7 [alpha<0]: Expected: -INFINITY\nActual:   %f\n", result);
    puts(isinf(result) && result < 0 ? "passed\n" : "failed\n");

    return 0;
}
