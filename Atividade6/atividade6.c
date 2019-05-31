#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <mpi/mpi.h>
#include "extra.h"

float * multiplica(float * matriz, float *vetor, int v_lin, int block){
    float temp;
    float * resultado;
    resultado = malloc(block*sizeof(float));
    for(int i = 0; i < block; i++){
        temp = 0;
        for(int j = 0; j < v_lin; j++){
            temp += matriz[i*block + j ] * vetor[j];
        }
        resultado[i] = temp;
    }
    return resultado;
}

int main(int argc, char **argv){
    MPI_Status status;
    FILE *m, *v, *f;
    int numtasks, rank, m_lin, m_col, v_lin, v_col, block;
    float *matriz, *vetor, *final, *temp, *temp2;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    if (rank == 0){
        m = fopen(argv[1], "r");
        v = fopen(argv[2], "r");
        // printf("%s\n%s\n", argv[1], argv[2]);
        matriz = lerMatriz(m, &m_lin, &m_col);
        vetor = lerMatriz(v, &v_lin, &v_col);
        final = malloc(m_lin*v_col * sizeof(float));
        block = m_lin/numtasks;
    }
    MPI_Bcast(&v_lin, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if(rank != 0) 
        vetor = malloc(v_lin * sizeof(float));
    MPI_Bcast(vetor, v_lin, MPI_FLOAT, 0, MPI_COMM_WORLD);

    MPI_Bcast(&block, 1, MPI_INT, 0, MPI_COMM_WORLD);
    temp = malloc(v_lin*block * sizeof(float));

    MPI_Scatter(matriz, block*v_lin, MPI_FLOAT, temp, block*v_lin, MPI_FLOAT, 0, MPI_COMM_WORLD);

    temp2 = multiplica(temp, vetor, v_lin, block);
    MPI_Gather(temp2, block, MPI_FLOAT, matriz, block, MPI_FLOAT, 0, MPI_COMM_WORLD);
    if(rank == 0 )
        // imprimirMatriz(matriz, m_lin, v_col);
        escreverMatriz(argv[3], matriz, m_lin, v_col);
    MPI_Finalize();
    return 0;
}