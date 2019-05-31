#include <stdio.h>
// #include "mpi.h"
#include <mpi/mpi.h>
#include <string.h>
#include <stdlib.h>

int printArrayForRank(int rank, int *array,  int arraySize) {
   int i;
   char *output = (char *) malloc((arraySize + 100) * 4 * sizeof(char));
   sprintf(output, "Rank %d: ", rank);
   for (int i = 0; i < arraySize; i++)
      sprintf(output, "%s %d", output, array[i]);
   sprintf(output,"%s\n", output);
   printf("%s", output);
   fflush(stdout);
   free(output);
   return i;
}

int MPI_Ring_broadcast(int *array, int arraySize, MPI_Comm comm) {
    int rank;
    MPI_Status status;
    MPI_Comm_rank(comm, &rank);
    if(rank == 0){
        MPI_Send(array, arraySize, MPI_INT, 1, 0, comm);
        MPI_Send(array, arraySize, MPI_INT, 15, 0, comm);
        return 1;
    }
    MPI_Recv(array, arraySize, MPI_INT, MPI_ANY_SOURCE, 0, comm, &status);

    if(rank < 7)
        MPI_Send(array, arraySize, MPI_INT, rank+1, 0, comm);
    else if( rank > 8)
        MPI_Send(array, arraySize, MPI_INT, rank-1, 0, comm);
    return 1;
}

int MPI_Mesh_broadcast(int *array, int arraySize, MPI_Comm comm) {
    int rank;
    MPI_Status status;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0){
        MPI_Send(array, arraySize, MPI_INT, 1, 0, comm);
        MPI_Send(array, arraySize, MPI_INT, 4, 0, comm);
        return 1;
    }
    MPI_Recv(array, arraySize, MPI_INT, MPI_ANY_SOURCE, 0, comm, &status);

    if (rank % 4 == 0){
        MPI_Send(array, arraySize, MPI_INT, rank+1, 0, comm);
        if( rank < 12)
            MPI_Send(array, arraySize, MPI_INT, rank+4, 0, comm);
        return 1;
    } else if ((rank + 1) % 4 != 0){
        MPI_Send(array, arraySize, MPI_INT, rank+1, 0, comm);
        return 1;
    }else{
        return 1;
    }
    return 0;
}


int main(int argc, char *argv[]) {
   int size, rank;
   int *array, arraySize;

   MPI_Init(&argc, &argv);
   MPI_Comm_size(MPI_COMM_WORLD, &size);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   
   arraySize = atoi(argv[1]);
   array = (int *) malloc(arraySize * sizeof(int));
 
   // Inicializa o array com 0.
   if (rank == 0) {
        for (int i = 0; i < arraySize; i++)
            array[i] = 0;
   }

   // Imprime o array inicial de todos os processos.
   printArrayForRank(rank, array, arraySize);

   // Faz broadcast usando uma topologia anel.
   MPI_Ring_broadcast(array, arraySize, MPI_COMM_WORLD);

   // Barreira de sincronização.
   MPI_Barrier(MPI_COMM_WORLD);

   // Imprime o array após o broadcast na topologia anel.
   printArrayForRank(rank, array, arraySize);
  
   // Barreira de sincronização.
   MPI_Barrier(MPI_COMM_WORLD);
   
   // Reconfigura o array com todos os elementos iguais a 1000.
   if (rank == 0) {
      for (int i = 0; i < arraySize; i++)
         array[i] =  1000;
   }

   // Faz broadcast usando uma topologia mesh.
   MPI_Mesh_broadcast(array, arraySize, MPI_COMM_WORLD);

   // Barreira de sincronização.
   MPI_Barrier(MPI_COMM_WORLD);

   // Imprime o array após o broadcast na topologia mesh.
   printArrayForRank(rank, array, arraySize);
     
   free(array);
   MPI_Finalize();
   return 0;
}