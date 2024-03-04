#include "fmm.h"

#define BLOCK_SIZE 16


void pack_matrix(int n, int *source_matrix, int leading_dimension_source, int *packed_matrix) {
    for (int i = 0; i < n; i++) { // Iterate over rows
        for (int j = 0; j < n; j++) { // Iterate over columns
            // Calculate pointers to the start of the current row and column in the source matrix
            int *source_element_ptr = &source_matrix[i * leading_dimension_source + j];
            // Calculate pointer to the position in the packed matrix where the current element should be copied
            int *packed_element_ptr = packed_matrix + i * n + j;
            // Copy the current element from source to packed matrix
            *packed_element_ptr = *source_element_ptr;
        }
    }
}

void matrix_multiply(int n, int *A, int *B, int *C) {
    // Create packed matrices for A and B
    int *packed_A = (int*)malloc(n * n * sizeof(int));
    int *packed_B = (int*)malloc(n * n * sizeof(int));
    pack_matrix(n, A, n, packed_A);
    pack_matrix(n, B, n, packed_B);

    // Perform matrix multiplication
    for (int i = 0; i < n; i+= BLOCK_SIZE){
        for (int j = 0; j < n; j += BLOCK_SIZE) {
            for (int k = 0; k < n; k += BLOCK_SIZE) {
                for (int row = i; row < i + BLOCK_SIZE; row++) {
                    for (int col = j; col < j + BLOCK_SIZE; col++) {
                        int sum = 0;
                        for (int inner = k; inner < k + BLOCK_SIZE; inner++) {
                            sum += packed_A[row * n + inner] * packed_B[inner * n + col];
                        }
                        C[row * n + col] += sum;
                    }
                }
            }
        }
    }

    // Free dynamically allocated memory
    free(packed_A);
    free(packed_B);
}

void fmm(int n, int* m1, int* m2, int* result) {
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < n; j++) {
//            result[i * n + j] = 0;  // result[i][j] = 0
//            for (int k = 0; k < n; k++)
//                result[i * n + j] += m1[i * n + k] * m2[k * n + j];  // result[i][j] += m1[i][k] * m2[k][j]
//        }
//    }
    matrix_multiply(n,m1,m2, result);
}

//void pack_matrix_columns(int num_columns, double *source_matrix, int leading_dimension_source, double *packed_matrix) {
//    // Iterate over each column of the source matrix
//    for (int column_index = 0; column_index < num_columns; column_index++) {
//        // Calculate the pointer to the start of the current column in the source matrix
//        double *source_column_ptr = &source_matrix[column_index * leading_dimension_source];
//
//        // Copy each element of the current column into the packed matrix
//        // Note: Assuming each column consists of exactly 4 elements
//        *packed_matrix = *source_column_ptr;                // Copy the first element
//        *(packed_matrix + 1) = *(source_column_ptr + 1);    // Copy the second element
//        *(packed_matrix + 2) = *(source_column_ptr + 2);    // Copy the third element
//        *(packed_matrix + 3) = *(source_column_ptr + 3);    // Copy the four
//    }
//    }
//void pack_matrix_rows(int num_rows, double *source_matrix, int leading_dimension_source, double *packed_matrix) {
//    // Define pointers to the starting elements of each row in source_matrix
//    double *source_row_pointers[] = {
//            &source_matrix[0 * leading_dimension_source],  // Pointer to the start of row 0
//            &source_matrix[1 * leading_dimension_source],  // Pointer to the start of row 1
//            &source_matrix[2 * leading_dimension_source],  // Pointer to the start of row 2
//            &source_matrix[3 * leading_dimension_source]   // Pointer to the start of row 3
//    };
//
//    // Loop over rows of source_matrix and pack them into packed_matrix
//    for (int row_index = 0; row_index < num_rows; row_index++) {
//        // Pointer to the start of the current row in packed_matrix
//        double *packed_row_ptr = packed_matrix + row_index * 4;
//
//        // Copy elements from source_matrix row by row into packed_matrix
//        for (int column_index = 0; column_index < 4; column_index++) {
//            packed_row_ptr[column_index] = source_row_pointers[column_index][row_index];
//        }
//    }
//}



