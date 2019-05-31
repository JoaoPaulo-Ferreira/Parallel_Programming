#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void loadData(FILE * f, float * buffer, int size){
    int i = 0, j = 0, int_part, dec_part, dec_len, aux_i = 0;
    char * line = NULL;
    char aux[10];
    size_t len = 0;
    size_t read;
    read = getline(&line, &len, f);
    if (read == -1)
        return;
    while(line[j] != '\n'){
        if(line[j] == '.'){
            aux[aux_i] = '\0';
            int_part = atoi(aux);
            bzero(aux, 10);
            aux_i = 0;
        }else if(line[j] == ':'){
            aux[aux_i] = '\0';
            dec_part = atoi(aux);
            if(dec_part > 0){
                dec_len = strlen(aux);
                buffer[i] = int_part + (pow(dec_part, dec_len * -1 ));
            }else{
                buffer[i] = int_part;
            }
            bzero(aux, 10);
            aux_i = 0;
            i++;
        }else
            aux[aux_i++] = line[j];
        j++;
    }
    aux[aux_i] = '\0';
    dec_part = atoi(aux);
    if(dec_part > 0){
        dec_len = strlen(aux);
        buffer[i] = int_part + (pow(dec_part, dec_len * -1 ));
    }else{
        buffer[i] = int_part;
    }
}

int main(int argc, char **argv){
    size_t len = 0;
    char * aux;
    float total;
    int m_cols = 0;
    int m_rows = 0;
    int v_cols = 0;
    int i = 0, j = 0;
    FILE * f_matrix = fopen(argv[1], "r");
    FILE * f_vector = fopen(argv[2], "r");
    FILE * f_result = fopen(argv[3], "w");
    if (f_matrix == NULL || f_vector == NULL)
        printf("Null found\n");
    getline(&aux, &len, f_matrix);
    m_rows = atoi(aux);
    getline(&aux, &len, f_matrix);
    m_cols = atoi(aux);
    getline(&aux, &len, f_vector);
    v_cols = atoi(aux);
    float vec[v_cols];
    float buffer[m_cols];
    loadData(f_matrix, buffer, m_cols);
    loadData(f_vector, vec, v_cols);
    fprintf(f_result, "%d\n", m_rows);
    for (i = 0; i < m_rows; i++){
        total = 0;
        for(j = 0; j < m_cols; j++){
            total += vec[j]*buffer[j];
        }
        fprintf(f_result, "%.2f", total);
        if(i < m_rows - 1)
            fprintf(f_result, ":");
        else
            fprintf(f_result, "\n");

        loadData(f_matrix, buffer, m_cols);
    }
    fclose(f_matrix);
    fclose(f_vector);
    fclose(f_result);
    return 0;
}