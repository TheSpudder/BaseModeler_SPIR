#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "../src/base.h"



int main (int argc, char **argv) {
    
    //Test 1
    double result = dbm_to_watts(10);
    double expected = 0.01;
    printf("\n");
    printf("Test 1 [10dbm]: Expected: %f W\nActual: %f W\n", expected, result);
    if (fabs(result - expected < 0.0001)) {
        puts("passed\n");
    }
    else {
        puts("failed test 1");
    }
    
    //Test 2
    result = dbm_to_watts(64);
    expected = 2511.8864;
    printf("Test 2 [64dbm]: Expected: %f W\nActual: %f W\n", expected, result);
    if (fabs(result - expected < 0.0001)) {
            puts("passed");
    }
    else {
         puts("failed test 2");
    }

    //Test 3 (large number test)
    result = dbm_to_watts(999);
    expected = pow(10, 96.9); 
    printf("\nTest 3 [999dbm]: Expected: %e W\nActual: %e W\n", expected, result);
    if (fabs(result - expected)/expected < 1e-5) puts("passed"); 
    else puts("failed test 3");
    
    //Test 4
    result = dbm_to_watts(0);
    expected = 0.001; 
    printf("\nTest 4 [0dbm]: Expected: %f W\nActual: %f W\n", expected, result);
    if (fabs(result - expected) < 0.0001) puts("passed"); 
    else puts("failed test 4");

    //Test 5 
    result = dbm_to_watts(-30);
    expected = 0.000001;
    printf("\nTest 5[-30dbm]: Expected: %f W\nActual: %f W\n", expected, result);
    if (fabs(result - expected) < 0.0000001) puts("passed"); 
    else puts("failed test 5");

    //Test 6
    result = dbm_to_watts(3.5);
    expected = pow(10, (3.5-30)/10);
    printf("\nTest 6 [3.5dbm]: Expected: %f W\nActual: %f W\n", expected, result);
    if (fabs(result - expected) < 0.00001) puts("passed"); 
    else puts("failed test 6");

    //Test 7
    result = dbm_to_watts(-5.7);
    expected = pow(10, (-5.7-30)/10);
    printf("\nTest 7 [-5.7dbm]: Expected: %f W\nActual: %f W\n", expected, result);
    if (fabs(result - expected) < 0.00001) puts("passed"); 
    else puts("failed test 7");

    return 0;
}


