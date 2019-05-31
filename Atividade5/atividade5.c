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
    float *matriz, *vetor, *final;
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
        // printf("linhas = %d colunas = %d\n", m_lin, m_col);
        for (int i = 1; i < numtasks; i++){
            MPI_Send(&v_lin, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(vetor, v_lin, MPI_FLOAT, i, 1, MPI_COMM_WORLD);
            MPI_Send(&block, 1, MPI_INT, i, 2, MPI_COMM_WORLD);
            MPI_Send(&matriz[i*m_col*block], block*m_col, MPI_FLOAT, i, 3, MPI_COMM_WORLD);
        }
        final = multiplica(matriz,vetor,v_lin,block);
        for(int i = 1; i < numtasks; i++)
            MPI_Recv(&final[i*block], block, MPI_FLOAT, i, 4, MPI_COMM_WORLD, &status);

        escreverMatriz(argv[3], final, m_lin, v_col);
        liberarMatriz(matriz);
        liberarMatriz(vetor);
        free(final);
        final = NULL;
    }else { //RANK != 0
        MPI_Recv(&v_lin, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        vetor =  (float *) malloc(v_lin * sizeof(float));
        MPI_Recv(vetor, v_lin, MPI_FLOAT, 0, 1, MPI_COMM_WORLD, &status);
        // 
        MPI_Recv(&block, 1, MPI_INT, 0, 2, MPI_COMM_WORLD, &status);
        matriz = (float *) malloc(v_lin * block * sizeof(float)); // v_lin == m_col
        MPI_Recv(matriz, v_lin*block, MPI_FLOAT, 0, 3, MPI_COMM_WORLD, &status);
        final = multiplica(matriz,vetor,v_lin,block);

        MPI_Send(final, block, MPI_FLOAT, 0, 4, MPI_COMM_WORLD);
        free(vetor);
        vetor = NULL;
        free(matriz);
        matriz = NULL; 
        // printf("rank %d: de = %d a = %d\n", rank, rank*v_lin*block, rank*v_lin*block + block*v_lin);
    }
    // printf("rank = %d\n", rank);
    MPI_Finalize();
    return 0;
}