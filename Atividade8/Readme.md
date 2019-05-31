Objetivo
Escrever duas funções em um programa MPI que faça um broadcast de uma mensagem definida pelo processo 0 à todos os outros processos. Cada função irá aplicar uma topologia diferente. Somente primitivas ponto-a-ponto podem ser utilizadas. Para este exercício, vamos considerar um número fixo de 16 processos.

Topologias
Iremos usar uma topologia anel e um mesh para o broadcast.

Anel
As seguinte função deve ser implementada:

int MPI_Ring_broadcast(int *array, int arraySize, MPI_Comm comm)

A função irá receber um array de inteiros e fazer um broadcast usando uma topologia anel. Por exemplo, para 16 processos, a comunicação deve seguir o seguinte padrão:

Mesh de Duas Dimensões
Será criado um grid de 2 dimensões, 4 por 4. A seguinte função deve ser implementada:

int MPI_Mesh_broadcast(int *array, int arraySize, MPI_Comm comm)

A função irá receber um array de inteiros e fazer um broadcast usando uma topologia mesh. Por exemplo, para 16 processos, a comunicação deve seguir o seguinte padrão:

Código Fonte Base
Utilizem o esqueleto abaixo para implementar as funções onde indicado.

#include <stdio.h>
#include "mpi.h"
#include <string.h>
#include <stdlib.h>

int printArrayForRank(int rank, int *array, int arraySize) {
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
}

int MPI_Mesh_broadcast(int *array, int arraySize, MPI_Comm comm) {
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
     array[i] = 1000;
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
Esse código recebe como parâmetro o tamanho do array a ser distribuído. Em seguinda, no rank 0, o vetor é inicializado com o valor 0 em todas as posições e depois a topologia anel é utilizada para distribuir o array. Em seguida, o rank 0 agora preenche o array com valores iguais a 1000. O novo array é distribuído com a topologia mesh. Uma execução com sucesso ficaria assim:

jmhal@saturn:~/repositorios/parallel/mpi/broadcast_topology$ mpicc broadcast_topology.c -o broadcast_topology
jmhal@saturn:~/repositorios/parallel/mpi/broadcast_topology$ mpirun -np 16 ./broadcast_topology 5
Rank 1: -456992608 21879 -457124640 21879 -457343856
Rank 6: -2138851168 21979 -2138983200 21979 -2139202416
Rank 8: 277755424 21968 277685568 21968 277466000
Rank 11: -1694967648 22100 -1695099680 22100 -1695318896
Rank 13: -660057664 22019 -659984272 22019 -660211808
Rank 3: 779491488 22022 779359456 22022 779140240
Rank 12: 1921460384 21871 1921328352 21871 1921109632
Rank 7: 210544800 22036 210412768 22036 210193552
Rank 2: -476931936 21899 -477063968 21899 -477283184
Rank 9: 1839429792 21948 1839297760 21948 1839078544
Rank 15: -1133156192 21963 -1133288224 21963 -1133506944
Rank 4: -1340454752 21911 -1340586784 21911 -1340806000
Rank 0: 0 0 0 0 0
Rank 14: 783587488 21975 783455456 21975 783236736
Rank 5: 850127008 21999 849994976 21999 849775760
Rank 10: -1445984096 21919 -1446116128 21919 -1446335344
Rank 8: 0 0 0 0 0
Rank 0: 0 0 0 0 0
Rank 4: 0 0 0 0 0
Rank 12: 0 0 0 0 0
Rank 1: 0 0 0 0 0
Rank 9: 0 0 0 0 0
Rank 13: 0 0 0 0 0
Rank 11: 0 0 0 0 0
Rank 15: 0 0 0 0 0
Rank 3: 0 0 0 0 0
Rank 7: 0 0 0 0 0
Rank 5: 0 0 0 0 0
Rank 10: 0 0 0 0 0
Rank 2: 0 0 0 0 0
Rank 14: 0 0 0 0 0
Rank 6: 0 0 0 0 0
Rank 11: 1000 1000 1000 1000 1000
Rank 7: 1000 1000 1000 1000 1000
Rank 15: 1000 1000 1000 1000 1000
Rank 13: 1000 1000 1000 1000 1000
Rank 1: 1000 1000 1000 1000 1000
Rank 3: 1000 1000 1000 1000 1000
Rank 9: 1000 1000 1000 1000 1000
Rank 6: 1000 1000 1000 1000 1000
Rank 14: 1000 1000 1000 1000 1000
Rank 2: 1000 1000 1000 1000 1000
Rank 10: 1000 1000 1000 1000 1000
Rank 5: 1000 1000 1000 1000 1000
Rank 12: 1000 1000 1000 1000 1000
Rank 4: 1000 1000 1000 1000 1000
Rank 0: 1000 1000 1000 1000 1000
Rank 8: 1000 1000 1000 1000 1000
Ao finalizar, coloque a versão final na pasta atividades/atividade08.
