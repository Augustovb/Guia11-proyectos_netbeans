/*
 * File:   newsimpletest.c
 * Author: augustovb
 *
 * Created on Jun 9, 2014, 8:33:52 AM
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * Simple C Test Suite
 */

void bitSet(unsigned char* byte, unsigned char bit, unsigned char value, int* pstate);

void testBitSet() {
    unsigned char* byte;
    unsigned char bit;
    unsigned char value;
    int* pstate;
    bitSet(byte, bit, value, pstate);
    if (1 /*check result*/) {
        printf("%%TEST_FAILED%% time=0 testname=testBitSet (newsimpletest) message=error message sample\n");
    }
}

unsigned char pow2(unsigned char ala);

void testPow2() {
    unsigned char ala;
    unsigned char result = pow2(ala);
    if (1 /*check result*/) {
        printf("%%TEST_FAILED%% time=0 testname=testPow2 (newsimpletest) message=error message sample\n");
    }
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% newsimpletest\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%%  testBitSet (newsimpletest)\n");
    testBitSet();
    printf("%%TEST_FINISHED%% time=0 testBitSet (newsimpletest)\n");

    printf("%%TEST_STARTED%%  testPow2 (newsimpletest)\n");
    testPow2();
    printf("%%TEST_FINISHED%% time=0 testPow2 (newsimpletest)\n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}
