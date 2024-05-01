#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define NUM_ROWS 2
#define NUM_COLS 2

void customMerge(int array[], int left, int mid, int right) {
    int i, j, k;
    int leftSize = mid - left + 1;
    int rightSize = right - mid;
    int leftArray[leftSize], rightArray[rightSize];
    for (i = 0; i < leftSize; i++)
        leftArray[i] = array[left + i];
    for (j = 0; j < rightSize; j++)
        rightArray[j] = array[mid + 1 + j];
    i = 0;
    j = 0;
    k = left;
    while (i < leftSize && j < rightSize) {
        if (leftArray[i] <= rightArray[j]) {
            array[k] = leftArray[i];
            i++;
        } else {
            array[k] = rightArray[j];
            j++;
        }
        k++;
    }
    while (i < leftSize) {
        array[k] = leftArray[i];
        i++;
        k++;
    }
    while (j < rightSize) {
        array[k] = rightArray[j];
        j++;
        k++;
    }
}

void customMergeSort(int array[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        customMergeSort(array, left, mid);
        customMergeSort(array, mid + 1, right);

        customMerge(array, left, mid, right);
    }
}

int main(int argc, char **argv) {
    int rank, numProcesses;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numProcesses);

    int matrix[NUM_ROWS][NUM_COLS];
    int sortedMatrix[NUM_ROWS][NUM_COLS]; 

    if (rank == 0) {
        printf("Enter matrix elements (%d x %d):\n", NUM_ROWS, NUM_COLS);
        for (int i = 0; i < NUM_ROWS; i++) {
            for (int j = 0; j < NUM_COLS; j++) {
                scanf("%d", &matrix[i][j]);
            }
        }
    }

    MPI_Bcast(matrix, NUM_ROWS * NUM_COLS, MPI_INT, 0, MPI_COMM_WORLD);

    long long int rowProduct = 1;
    for (int i = 0; i < NUM_ROWS; i++) {
        if (i % numProcesses == rank) {
            customMergeSort(matrix[i], 0, NUM_COLS - 1); 
            for (int j = 0; j < NUM_COLS; j++) {
                sortedMatrix[i][j] = matrix[i][j]; 
                rowProduct *= matrix[i][j]; 
            }
        }
    }

    MPI_Gather(sortedMatrix[rank], NUM_COLS, MPI_INT, matrix, NUM_COLS, MPI_INT, 0, MPI_COMM_WORLD);

    long long int matrixProduct;
    MPI_Reduce(&rowProduct, &matrixProduct, 1, MPI_LONG_LONG, MPI_PROD, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Sorted matrix:\n");
        for (int i = 0; i < NUM_ROWS; i++) {
            for (int j = 0; j < NUM_COLS; j++) {
                printf("%d ", matrix[i][j]);
            }
            printf("\n");
        }
        printf("Product of the complete matrix: %lld\n", matrixProduct);
    }

    MPI_Finalize();
    return 0;
}

