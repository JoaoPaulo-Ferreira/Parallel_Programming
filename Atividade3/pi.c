#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <mpi/mpi.h>
    
float MonteCarlosPi(int n){
    if(n == 0)
        return 0;

    float x = 0, y = 0;
    int acertos = 0, i;
    for( i = 0; i < n; i++){
        x=((float)rand()/(float)(RAND_MAX));
        y=((float)rand()/(float)(RAND_MAX));
        // printf("x = %.2f y = %.2f\n", x,y);
        if((x * x + y * y < 1))
            acertos += 1;
    }
    return acertos;
    // return 4 * (float)acertos / (float)n;
}

int main(int argc, char **argv){
    MPI_Status status;
    int numtasks, rank, i, n = 0;
    int blockSize, task;
    float totalAcertos = 0, temp, pi = 0;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    srand((unsigned int ) time(0));
    if (!rank){
        n = atoi(argv[1]);
        blockSize = n/numtasks;
        for( i = 1; i < numtasks; i++){
            MPI_Send(&blockSize, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }

        totalAcertos = MonteCarlosPi(blockSize);

        for( i = 1; i < numtasks; i++){
            MPI_Recv(&temp, 1, MPI_FLOAT, i, 1, MPI_COMM_WORLD, &status);
            totalAcertos += temp;
        }
        pi = 4 * totalAcertos/(float)n;
        printf("%.5f\n", pi);
        
    } else {
        MPI_Recv(&blockSize, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        totalAcertos += MonteCarlosPi(blockSize);
        MPI_Send(&totalAcertos, 1, MPI_FLOAT, 0, 1, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}