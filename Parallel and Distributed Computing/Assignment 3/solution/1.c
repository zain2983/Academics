#include <stdio.h>
#include <mpi.h>

#define ROWS 4
#define COLS 4

int main(int argc, char **argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int matrix[ROWS][COLS] = {
        {1, 3, 5, 7},
        {2, 4, 6, 8},
        {11, 13, 15, 17},
        {12, 14, 16, 18}
    };

    int my_row[COLS];
    MPI_Scatter(matrix, COLS, MPI_INT, my_row, COLS, MPI_INT, 0, MPI_COMM_WORLD);

    int transposed_row[ROWS];
    MPI_Alltoall(my_row, 1, MPI_INT, transposed_row, 1, MPI_INT, MPI_COMM_WORLD);

    printf("Transposed row at process %d:\n", rank);
    for (int i = 0; i < ROWS; i++) {
        printf("%d ", transposed_row[i]);
    }
    printf("\n");

    MPI_Finalize();
    return 0;
}

