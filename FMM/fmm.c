#include "fmm.h"

void fmm(int n, int* m1, int* m2, int* result) {

    int i, j, k;
    int in;
    int kn;
//
//    for ( i = 0; i < n; i++) {
//        in = i*n;
//        for ( j = 0; j < n; j++) {
//            int sum = 0;
//            for ( k = 0; k < n; k++) {
//                kn = k*n;
//                // open inner loop:  improve spatial locality by accessing contiguous memory locations within the loop.
//                sum += m1[in + k] * m2[kn + j];
//            }
//            result[in + j] = sum;
//        }
//    }

    int r;
    int s;
    int x;
    int remainder = n % 16;

    for (i = 0; i < n * n; i++) {
        result[i] = 0;
    }

    for (i = 0; i < n; i++) {
        in = i*n;
        kn = 0;
        for ( k = 0; k < n; k++) {
            r = m1[in +k];
            for (j = 0; j < n-16; j += 16) {
                s = in + j;
                x = kn + j;
                result[s] += r * m2[x];
                result[s++] += r * m2[x++];
                result[s + 2] += r * m2[x + 2];
                result[s + 3] += r * m2[x + 3];
                result[s + 4] += r * m2[x + 4];
                result[s + 5] += r * m2[x + 5];
                result[s + 6] += r * m2[x + 6];
                result[s + 7] += r * m2[x + 7];
                result[s + 8] += r * m2[x + 8];
                result[s + 9] += r * m2[x + 9];
                result[s + 10] += r * m2[x + 10];
                result[s + 11] += r * m2[x+ 11];
                result[s + 12] += r * m2[x + 12];
                result[s + 13] += r * m2[x + 13];
                result[s + 14] += r * m2[x + 14];
                result[s + 15] += r * m2[x + 15];
                s += 16;
                x += 16;
//                result[s + 16] += r * m2[x + 16];
//                result[s + 17] += r * m2[x + 17];
//                result[s + 18] += r * m2[x + 18];
//                result[s + 19] += r * m2[x + 19];
            }
            for (j = 0;j < remainder; j++){
                result[s + j]= r * m2[x + j];
            }
            kn +=n;
        }
    }

//    for ( i = 0; i < n; i++) {
//        in = i*n;
//        for ( k = 0; k < n; k++) {
//            kn = k*n;
//            // r = result[in + k];
//            for ( j = 0; j < n; j++) {
//                result[in + j] += m1[in + k] * m2[kn + j];
//            }
//        }
//    }

//    for (i = 0; i < n; i++) {
//        for (k = 0; k < n; k++) {
//            for (j = 0; j < n; j += 2) { // Unroll inner loop by 2
//                result[i * n + j] += m1[i * n + k] * m2[k * n + j];
//                result[i * n + j + 1] += m1[i * n + k] * m2[k * n + j + 1];
//            }
//        }
//    }

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







