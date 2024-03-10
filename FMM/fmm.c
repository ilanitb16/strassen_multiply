#include "fmm.h"

void fmm(int n, int* m1, int* m2, int* result) {

    // optimize like we learned in the lecture
    int i, j, k,s ,x;
    int in;
    int kn;

    for (i = 0; i < n * n; i++) {
        result[i] = 0;
    }

    for ( i = 0; i < n; i++) {
    in = i*n;
        for ( k = 0; k < n; k++) {
            kn = k*n;
            for ( j = 0; j < n; j++) {
                s = in + j;
                x = kn + j;
                result[s] += m1[in + k] * m2[x];
            }
        }
    }

//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < n; j++) {
//            result[i * n + j] = 0;  // result[i][j] = 0
//            for (int k = 0; k < n; k++)
//                result[i * n + j] += m1[i * n + k] * m2[k * n + j];  // result[i][j] += m1[i][k] * m2[k][j]
//        }
//    }
}







