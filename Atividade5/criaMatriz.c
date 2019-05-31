#include <stdio.h>
#include <stdlib.h>
// #include <time.h>

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
	        fprintf(arquivo, "%.1f:", valor);
	     else
	        fprintf(arquivo, "%.1f", valor);
	  }
      fprintf(arquivo, "\n");
   }

   // Fecha arquivo.
   fclose(arquivo);

   return 0;
}