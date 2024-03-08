#include "fmm.h"

#define BLOCK_SIZE 16

#include <stdlib.h>
#include <stdio.h>


void fmm(int n, int* m1, int* m2, int* result) {

//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < n; j++) {
//            int sum = 0;
//            for (int k = 0; k < n; k++) {
//                // open inner loop:  improve spatial locality by accessing contiguous memory locations within the loop.
//                sum += m1[i * n + k] * m2[k * n + j];
//            }
//            result[i * n + j] = sum;
//        }
//    }

    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            for (int j = 0; j < n; j++) {
                result[i * n + j] += m1[i * n + k] * m2[k * n + j];
            }
        }
    }

    // result[i * n + j]: element at row i and column j in the result matrix.
    // m1[i * n + k]: element at row i and column k
    // m2[k * n + j]: element at row k and column j

    // improve spatial locality by accessing contiguous memory locations within the loop.
    // Sequential access patterns are more cache-friendly


//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < n; j++) {
//            result[i * n + j] = 0;  // result[i][j] = 0
//            for (int k = 0; k < n; k++)
//                result[i * n + j] += m1[i * n + k] * m2[k * n + j];  // result[i][j] += m1[i][k] * m2[k][j]
//        }
//    }
}







