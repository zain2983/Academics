#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

void CompareSplit(int nlocal, int *elements, int *relements, int *wspace, int keepsmall);

int IncOrder(const void *el, const void *e2);

int main(int argc, char *argv[]) {

    int n; /* The total number of elements to be sorted */
    int npes; /* The total number of processes */
    int rank; /* The rank of the calling process */
    int nlocal; /* The local number of elements, and the array that stores them */
    int *elements; /* The array that stores the local elements */
    int *relements; /* The array that stores the received elements */
    int *wspace; /* Working space during the compare-split operation */
    int oddrank; /* The rank of the partner during odd-phase communication */
    int evenrank; /* The rank of the partner during even-phase communication */
    int i;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &npes);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    n = atoi(argv[1]);
    nlocal = n / npes; /* Compute the number of elements to be stored locally. */

    elements = (int *)malloc(nlocal * sizeof(int));
    relements = (int *)malloc(nlocal * sizeof(int));
    wspace = (int *)malloc(nlocal * sizeof(int));

    srand(rank); // Seed the random number generator with the process rank
    for (i = 0; i < nlocal; i++)
        elements[i] = rand(); // Generate random values for elements array

    qsort(elements, nlocal, sizeof(int), IncOrder);

    if (rank % 2 == 0) {
        oddrank = rank - 1;
        evenrank = rank + 1;
    } else {
        oddrank = rank + 1;
        evenrank = rank - 1;
    }

    if (oddrank == -1 || oddrank == npes)
        oddrank = MPI_PROC_NULL;
    if (evenrank == -1 || evenrank == npes)
        evenrank = MPI_PROC_NULL;

    for (i = 0; i < npes - 1; i++) {
        if (i % 2 == 1) { /* odd phase */
            MPI_Sendrecv(elements, nlocal, MPI_INT, oddrank, 1, relements, nlocal, MPI_INT, oddrank, 1, MPI_COMM_WORLD, &status);
        } else { /* even phase */
            MPI_Sendrecv(elements, nlocal, MPI_INT, evenrank, 1, relements, nlocal, MPI_INT, evenrank, 1, MPI_COMM_WORLD, &status);
        }

        CompareSplit(nlocal, elements, relements, wspace, rank < status.MPI_SOURCE);
    }

    free(elements);
    free(relements);
    free(wspace);
    MPI_Finalize();

    return 0;
}

void CompareSplit(int nlocal, int *elements, int *relements, int *wspace, int keepsmall) {
    int i, j, k;

    for (i = 0; i < nlocal; i++)
        wspace[i] = elements[i]; /* copy the elements array into the wspace array */

    if (keepsmall) { /* keep the nlocal smaller elements */
        for (i = j = k = 0; k < nlocal; k++) {
            if (j == nlocal || (i < nlocal && wspace[i] < relements[j]))
                elements[k] = wspace[i++];
            else
                elements[k] = relements[j++];
        }
    } else { /* keep the nlocal larger elements */
        for (i = k = nlocal - 1, j = nlocal - 1; k >= 0; k--) {
            if (j == -1 || (i >= 0 && wspace[i] >= relements[j]))
                elements[k] = wspace[i--];
            else
                elements[k] = relements[j--];
        }
    }
}

/* The IncOrder function that is called by qsort is defined as follows */
int IncOrder(const void *el, const void *e2) {
    return (*((int *)el) - *((int *)e2));
}

