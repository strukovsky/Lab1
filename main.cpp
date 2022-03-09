#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

void star(int M, int center, int star_part_rank)
{
    int received;
    MPI_Status status;
    const int tag = 228;
    for (int iterateReceive = 0; iterateReceive < M; iterateReceive++)
    {
        MPI_Recv(&received, 1, MPI_INT, center, tag, MPI_COMM_WORLD, &status);
        printf("Received in star part %d: %d \n", star_part_rank, received);
    }
}

void center(int N, int M)
{
    for (int iterateMessage = 0; iterateMessage < M; iterateMessage++)
    {
        for (int iterateStarParts = 1; iterateStarParts <= N; iterateStarParts++)
        {
            int message = rand();
            const int tag = 228;
            printf("Center is about to send to %d message: %d\n", iterateStarParts, message);
            MPI_Send(&message, 1, MPI_INT, iterateStarParts, tag, MPI_COMM_WORLD);
        }
    }
}

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    int processes_count, current_process_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &current_process_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &processes_count);
    int M = 2;                   // how much times should be performed cycle
    int N = processes_count - 1; // Count of star parts
    if (current_process_rank == 0)
    {
        center(N, M);
    }
    else
    {
        star(M, 0, current_process_rank);
    }
    MPI_Finalize();
}
