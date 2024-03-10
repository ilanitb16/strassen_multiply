#include "fmm.h"

#define BLOCK_SIZE 16

#include <stdlib.h>
#include <stdio.h>


void add_matrices(int *result, int *a, int *b, int size) {
    for (int i = 0; i < size * size; i++) {
        result[i] = a[i] + b[i];
    }
}

void subtract_matrices(int *result, int *a, int *b, int size) {
    for (int i = 0; i < size * size; i++) {
        result[i] = a[i] - b[i];
    }
}

void strassen_multiply(int *result, int *mat1, int *mat2, int n) {
    if (n == 1) {
        result[0] = mat1[0] * mat2[0];
        return;
    }

    int m = n / 2; // Size of submatrices

    // Allocate memory for submatrices
    int *a11 = (int*)malloc(m * m * sizeof(int));
    int *a12 = (int*)malloc(m * m * sizeof(int));
    int *a21 = (int*)malloc(m * m * sizeof(int));
    int *a22 = (int*)malloc(m * m * sizeof(int));
    int *b11 = (int*)malloc(m * m * sizeof(int));
    int *b12 = (int*)malloc(m * m * sizeof(int));
    int *b21 = (int*)malloc(m * m * sizeof(int));
    int *b22 = (int*)malloc(m * m * sizeof(int));
    int *c11 = (int*)malloc(m * m * sizeof(int));
    int *c12 = (int*)malloc(m * m * sizeof(int));
    int *c21 = (int*)malloc(m * m * sizeof(int));
    int *c22 = (int*)malloc(m * m * sizeof(int));
    int *p = (int*)malloc(m * m * sizeof(int));
    int *q = (int*)malloc(m * m * sizeof(int));
    int *r = (int*)malloc(m * m * sizeof(int));
    int *s = (int*)malloc(m * m * sizeof(int));
    int *t = (int*)malloc(m * m * sizeof(int));
    int *u = (int*)malloc(m * m * sizeof(int));
    int *v = (int*)malloc(m * m * sizeof(int));
    int *t1 = (int*)malloc(m * m * sizeof(int));
    int *t2 = (int*)malloc(m * m * sizeof(int));

    // Populate submatrices
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            a11[i * m + j] = mat1[i * n + j];
            a12[i * m + j] = mat1[i * n + j + m];
            a21[i * m + j] = mat1[(i + m) * n + j];
            a22[i * m + j] = mat1[(i + m) * n + j + m];
            b11[i * m + j] = mat2[i * n + j];
            b12[i * m + j] = mat2[i * n + j + m];
            b21[i * m + j] = mat2[(i + m) * n + j];
            b22[i * m + j] = mat2[(i + m) * n + j + m];
        }
    }

    // Recursive calls for submatrices
    int *temp1 = (int*)malloc(m * m * sizeof(int));
    int *temp2 = (int*)malloc(m * m * sizeof(int));

    // Calculate p, q, r, s, t, u, v
    add_matrices(temp1, a11, a22, m);
    add_matrices(temp2, b11, b22, m);
    strassen_multiply(p, temp1, temp2, m);

    add_matrices(temp1, a21, a22, m);
    strassen_multiply(q, temp1, b11, m);

    subtract_matrices(temp1, b12, b22, m);
    strassen_multiply(r, a11, temp1, m);

    subtract_matrices(temp1, b21, b11, m);
    strassen_multiply(s, a22, temp1, m);

    add_matrices(temp1, a11, a12, m);
    strassen_multiply(t, temp1, b22, m);

    subtract_matrices(temp1, a21, a11, m);
    add_matrices(temp2, b11, b12, m);
    strassen_multiply(u, temp1, temp2, m);

    subtract_matrices(temp1, a12, a22, m);
    add_matrices(temp2, b21, b22, m);
    strassen_multiply(v, temp1, temp2, m);

    // Combine results into result matrix
    add_matrices(temp1, p, s, m);
    add_matrices(temp2, v, temp1, m);
    subtract_matrices(c11, temp2, t, m);
    add_matrices(c12, r, t, m);
    add_matrices(c21, q, s, m);
    add_matrices(temp1, p, r, m);
    add_matrices(temp2, u, temp1, m);
    subtract_matrices(c22, temp2, q, m);

    // Copy submatrices to the result matrix
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            result[i * n + j] = c11[i * m + j];
            result[i * n + j + m] = c12[i * m + j];
            result[(i + m) * n + j] = c21[i * m + j];
            result[(i + m) * n + j + m] = c22[i * m + j];
        }
    }

    // Free dynamically allocated memory
    free(a11);
    free(a12);
    free(a21);
    free(a22);
    free(b11);
    free(b12);
    free(b21);
    free(b22);
    free(c11);
    free(c12);
    free(c21);
    free(c22);
    free(p);
    free(q);
    free(r);
    free(s);
    free(t);
    free(u);
    free(v);
    free(t1);
    free(t2);
    free(temp1);
    free(temp2);
}

void fmm(int n, int* m1, int* m2, int* result) {
// Check if n is odd
    if (n % 2 != 0) {
        // Pad matrices with zeros to make dimensions even
        int padded_size = n + 1; // New size with padding
        int* padded_m1 = (int*)malloc(padded_size * padded_size * sizeof(int));
        int* padded_m2 = (int*)malloc(padded_size * padded_size * sizeof(int));
        int* padded_result = (int*)malloc(padded_size * padded_size * sizeof(int));

        // Copy original matrices to padded matrices
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                padded_m1[i * padded_size + j] = m1[i * n + j];
                padded_m2[i * padded_size + j] = m2[i * n + j];
            }
        }

        // Fill padded regions with zeros
        for (int i = 0; i < padded_size; i++) {
            for (int j = n; j < padded_size; j++) {
                padded_m1[i * padded_size + j] = 0;
                padded_m2[i * padded_size + j] = 0;
            }
        }

        // Perform matrix multiplication on padded matrices
        strassen_multiply(padded_result, padded_m1, padded_m2, padded_size);

        // Copy result to original size
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                result[i * n + j] = padded_result[i * padded_size + j];
            }
        }

        // Free memory for padded matrices and result
        free(padded_m1);
        free(padded_m2);
        free(padded_result);
    } else {
        // If n is even, perform matrix multiplication directly
        strassen_multiply(result, m1, m2, n);
    }}