#include "fmm.h"
#define BUFFER_SIZE 512


int main() {
    char f1[BUFFER_SIZE] = {0};
    char f2[BUFFER_SIZE] = {0};
    char f3[BUFFER_SIZE] = {0};
    int n;


    printf("First matrix: ");
    scanf("%s", f1);
    printf("Second matrix: ");
    scanf("%s", f2);
    printf("Result path: ");
    scanf("%s", f3);
    printf("Size: ");
    scanf("%d", &n);


    double time = measure_time(f1, f2, f3, n);
    //double time = measure_time("../FMM/mat1.txt", "../FMM/mat2.txt", "../FMM/result.txt", 3);
    //double time = measure_time("../FMM/mat1000-1.txt", "../FMM/mat1000-2.txt", "../FMM/result.txt", 1000);

    printf("Total time: %f ms\n", time);
}

