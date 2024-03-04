#include "fmm.h"

int* create_matrix(char* file_name, int n) {
    int* mat;

    int fd = open(file_name, O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("open error");
        exit(1);
    }

    if (ftruncate(fd, n * n * sizeof(int)) == -1) {
        perror("ftruncate error");
        exit(1);
    }

    mat = mmap(NULL, n * n * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mat == MAP_FAILED) {
        perror("mmap error");
        exit(1);
    }

    close(fd);
    return mat;
}

int* read_matrix(char* file_name, int n) {
    int* mat;

    int fd = open(file_name, O_RDONLY);
    if (fd == -1) {
        perror("open error");
        exit(1);
    }

    mat = mmap(NULL, n * n * sizeof(int), PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    if (mat == MAP_FAILED) {
        perror("mmap error");
        exit(1);
    }

    close(fd);
    return mat;
}

void free_matrix(int* mat, int n) {
    munmap(mat, n * n * sizeof(int));
}

void print_matrix(int* mat, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", mat[i * n + j]);
        }
        puts("");
    }
}

double measure_time(char* file1, char* file2, char* file_result, int n) {
	struct timeval startTime;
	struct timeval endTime;
	struct rusage ru;

    int* m1 = read_matrix(file1, n);
    int* m2 = read_matrix(file2, n);
    int* result = create_matrix(file_result, n);

	getrusage(RUSAGE_SELF, &ru); // start timer
	startTime = ru.ru_utime;

    fmm(n, m1, m2, result);

    getrusage(RUSAGE_SELF, &ru); // end timer
    endTime = ru.ru_utime;
    double tS = startTime.tv_sec * 1000000.0 + (startTime.tv_usec);
    double tE = endTime.tv_sec * 1000000.0 + (endTime.tv_usec);

    free_matrix(m1, n);
    free_matrix(m2, n);
    free_matrix(result, n);

    return (tE - tS) / 1000.0;
}

void subtract_matrices(int* mat1, int* mat2, int* result, int n) {
    for (int i = 0; i < n * n; i++) {
        result[i] = mat1[i] - mat2[i];
    }
}

void add_matrices(int* mat1, int* mat2, int* result, int n) {
    for (int i = 0; i < n * n; i++) {
        result[i] = mat1[i] + mat2[i];
    }
}

void strassen_multiply(int* mat1, int* mat2, int* result, int n) {
    if (n == 1) {
        result[0] = mat1[0] * mat2[0];
        return;
    }

    int newSize = n / 2;
    int* A11 = mat1;
    int* A12 = mat1 + newSize;
    int* A21 = mat1 + newSize * n;
    int* A22 = mat1 + newSize * n + newSize;

    int* B11 = mat2;
    int* B12 = mat2 + newSize;
    int* B21 = mat2 + newSize * n;
    int* B22 = mat2 + newSize * n + newSize;

    int* M1 = (int*)malloc(newSize * newSize * sizeof(int));
    int* M2 = (int*)malloc(newSize * newSize * sizeof(int));
    int* M3 = (int*)malloc(newSize * newSize * sizeof(int));
    int* M4 = (int*)malloc(newSize * newSize * sizeof(int));
    int* M5 = (int*)malloc(newSize * newSize * sizeof(int));
    int* M6 = (int*)malloc(newSize * newSize * sizeof(int));
    int* M7 = (int*)malloc(newSize * newSize * sizeof(int));

    int* temp1 = (int*)malloc(newSize * newSize * sizeof(int));
    int* temp2 = (int*)malloc(newSize * newSize * sizeof(int));

    // Calculating M1
    subtract_matrices(B12, B22, temp1, newSize);
    strassen_multiply(A11, temp1, M1, newSize);

    // Calculating M2
    strassen_multiply(A11, B22, M2, newSize);

    // Calculating M3
    strassen_multiply(A22, B11, M3, newSize);

    // Calculating M4
    subtract_matrices(B21, B11, temp1, newSize);
    strassen_multiply(A22, temp1, M4, newSize);

    // Calculating M5
    strassen_multiply(A11, B22, temp1, newSize);
    strassen_multiply(A22, B22, temp2, newSize);
    subtract_matrices(temp1, temp2, M5, newSize);

    // Calculating M6
    strassen_multiply(A12, B11, temp1, newSize);
    strassen_multiply(A22, B21, temp2, newSize);
    subtract_matrices(temp1, temp2, M6, newSize);

    // Calculating M7
    strassen_multiply(A11, B12, temp1, newSize);
    strassen_multiply(A21, B22, temp2, newSize);
    subtract_matrices(temp1, temp2, M7, newSize);

    // Calculating C11
    subtract_matrices(M2, M3, temp1, newSize); // M2 - M3
    add_matrices(M1, temp1, temp2, newSize); // M1 + M2 - M3
    add_matrices(temp2, M6, result, newSize); // M1 + M2 - M3 + M6

    // Calculating C12
    add_matrices(M1, M2, result + newSize, newSize);

    // Calculating C21
    add_matrices(M3, M4, result + newSize * n, newSize);

    // Calculating C22
    subtract_matrices(M1, M2, temp1, newSize); // M1 - M2
    add_matrices(temp1, M5, temp2, newSize); // M1 - M2 + M5
    subtract_matrices(temp2, M4, result + newSize * n + newSize, newSize); // M1 - M2 + M5 - M4

    free(M1);
    free(M2);
    free(M3);
    free(M4);
    free(M5);
    free(M6);
    free(M7);
    free(temp1);
    free(temp2);
}


