#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "../src/base.c"



int main (int argc, char **argv) {
    //positive num
    double result_1 = dbm_to_watts(10);
    double expected_1 = 0.01;
    printf("Expected: 0.01 W " "Actual: ""&f, result" "W");
    if (result_1 == expected_1) {
    puts("passed");
    }
    else {
        puts("failed");
    }
    //negative num

    //decimal / negative decimal

    //random val
    
}
