#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _EXTRA_H_
#define _EXTRA_H_

float *lerMatriz(FILE *arquivoMatriz, int *linhas, int *colunas){
    char *line = NULL;
    char *temp;
    float * matrix;
    size_t len = 0;
    getline(&line, &len, arquivoMatriz);
    *linhas = atoi(line);
    getline(&line, &len, arquivoMatriz);
    *colunas = atoi(line);
    matrix = (float * ) malloc (*linhas**colunas*sizeof(float));
    for(int i = 0; i < *linhas; i++){
        getline(&line, &len, arquivoMatriz);
        temp = strtok(line, ":");
        for(int j = 0; j < *colunas; j++){    
            matrix[*colunas * i + j] = atof(temp);
            temp = strtok(NULL, ":");
        }
    }
    return matrix;
}

void imprimirMatriz(float *m, int linhas, int colunas){
    for(int i = 0; i < linhas; i++ ){
        for(int j = 0; j < colunas; j++){
            printf("%.2f ", m[colunas * i + j]);
        }
        printf("\n");
    }
    
}

void escreverMatriz(char *nomeDoArquivo, float *m, int linhas, int colunas){
    int i, j;
    FILE *file;
    file = fopen(nomeDoArquivo, "w");
    if(file == NULL){
        printf("Erro ao abrir arquivo\n");
        exit(0);
    }
    fprintf(file,"%d\n%d\n",linhas, colunas);
    for(i = 0 ; i < linhas; i++){
        for(j = 0; j < colunas; j++){
            j == (colunas -1) ? 
            fprintf(file,"%.1f\n", m[colunas * i + j]) : 
            fprintf(file,"%.1f:", m[colunas * i + j]);
        }
    }
    fclose(file);
}

void liberarMatriz(float *m){
    free(m);
    m == NULL;
}

#endif //_EXTRA_H_