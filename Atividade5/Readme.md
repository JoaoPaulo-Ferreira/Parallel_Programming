Objetivo
O objetivo desta atividade é realizar a implementação paralela da multiplicação matriz/vetor. É uma expansão do que já foi feito na Atividade 02. Nesta atividade, só devem ser usadas operações ponto-a-ponto bloqueantes do MPI.

Execução
Seu programa deve receber da mesma forma três parâmetros:

O nome do arquivo contendo a matriz.
O nome do arquivo contendo o vetor.
O nome do arquivo que armazenará o resultado.
Portanto, a execução se dará da seguinte forma:

$ mpicc multiplicacaoMatrizVetorParalelo.c
$ mpirun -np 2 ./a.out matriz.txt vetor.txt resultado.txt
Irei testar para 2, 4 e 8 processos e matrizes de 1000 e 10000 com vetores de tamanhos compatíveis. O programa a seguir, chamado criarMatriz.c, recebe três parâmetros: quantidade de linhas, quantidade de colunas e o nome do arquivo.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
  // Recuperar as dimensões da matriz.
  int linhas = atoi(argv[1]);
  int colunas = atoi(argv[2]);

  // Recuperar nome do arquivo para salvar a matriz.
  char *nomeDoArquivo = argv[3];

  // Abrir arquivo para escrita.
  FILE *arquivo = fopen(nomeDoArquivo, "w+");

  // Escreve as dimensões.
  fprintf(arquivo, "%d\n", linhas);
  fprintf(arquivo, "%d\n", colunas);
  for (int i = 0; i < linhas; i++) {
   for (int j = 0; j < colunas; j++) {
	   float valor = 1.0;
	   if (j < colunas - 1)
	    fprintf(arquivo, "%05.2f:", valor);
	   else
	    fprintf(arquivo, "%05.2f", valor);
	 }
   fprintf(arquivo, "\n");
  }

  // Fecha arquivo.
  fclose(arquivo);

  return 0;
}
Por exemplo, a seguinte invocação:

$ ./criarMatriz 100 100 matriz100x100.txt
Irá criar um arquivo com uma matriz de 100 linhas com 100 colunas e todos os valores em 1.0. Você pode usar esse programa para gerar matriz de tamanhos e dimensões diferentes para testar seu programa. Sugestão: execute tantoa versão seria quanto a paralela dos dois programas e compare o resultado para as mesmas matrizes e vetores. Se o resultado for igual, é um forte indício que seu programa está correto.

Formato do Arquivos de Entrada e Saída
Você não precisa implementar as funções da Atividade Extra, mas o formato da entrada e saída será atualizado para como descrito lá. Em outras palavras, tanto a matriz quanto o vetor terão o mesmo formato de entrada:

linhas
colunas
elemento:elemento:elemento: ... :elemento
elemento:elemento:elemento: ... :elemento
elemento:elemento:elemento: ... :elemento
...
elemento:elemento:elemento: ... :elemento
Qualquer dúvida sobre o formato, me consultem na sala de aula ou no fórum #general.

Problema
Vamos utilizar a distribuição de blocos de linhas. Considerando uma matriz A e um vetor B, o vetor é enviado para todos os processos. Cada processo recebe uma quantidade (Número de Linhas) / (Número de Processos) de linhas da matriz A. A multiplicação local é feita e o resultado consolidado no processo de rank 0, que guarda o resultado em arquivo. Considere o seguinte esquema geral:

Processo 0:

Recupera os nomes dos arquivos da matriz, vetor e resultado.
Carrega a matriz e o vetor na memória.
Envia o vetor para os outros processos
Calcula a quantidade de trabalho local (número de linhas) que cada processo irá realizar.
Envia as partições das matrizes para os outros processos.
Faz seu cálculo local.
Recebe as contribuições de todos os outros processos.
Consolida o resultado na memória e salva em arquivo.
Processo i (i diferente de 0):

Recebe o vetor do processo 0.
Calcula a quantidade de trabalho local.
Recebe a partição da matriz.
Faz seu cálculo local.
Envia para o processo 0 sua contribuição.
Resultado
Coloque a solução na pasta atividades/atividade05.
