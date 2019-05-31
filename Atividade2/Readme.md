Objetivo
O objetivo desta atividade é realizar a implementação serial da multiplicação matriz/vetor. Nas próximas atividades iremos paralelizar essa versão inicial.

Crie uma pasta atividades/atividade02 no servidor e coloque seu programa nela.

Execução
Seu programa deve receber três parâmetros:

O nome do arquivo contendo a matriz.
O nome do arquivo contendo o vetor.
O nome do arquivo que armazenará o resultado.
Portanto, a execução se dará da seguinte forma:

$ gcc multiplicacaoMatrizVetor.c
$ ./a.out matriz.txt vetor.txt resultado.txt
Formato do Arquivos de Entrada e Saída
O arquivo da Matriz deve ter o seguinte formato:

A primeira linha deve conter o número de linhas da matriz;
a segunda linha deve conter o número de colunas da matriz;
o restante das linhas deve conter a matriz, linha por linha, com os elementos separados por : (dois pontos).
Por exemplo, uma matriz com 3 linhas e 4 colunas seria assim representada:

3
4
1.0:1.0:1.0:1.0
1.0:1.0:1.0:1.0
1.0:1.0:1.0:1.0
Já o arquivo do vetor tem formato semelhante, mas como é apenas uma dimensão, é mais simples. Por exemplo um vetor de 4 elementos seria informado assim:

4
1.0:1.0:1.0:1.0
Estou usando 1.0 nos exemplos, mas qualquer valor ponto flutuante deve ser aceito. Vamos usar o tipo de dados float. A saída deve ter o mesmo formato do vetor. Observe :

$ cat matriz.txt 
3
4
1.0:1.0:1.0:1.0
1.0:1.0:1.0:1.0
1.0:1.0:1.0:1.0
$ cat vetor.txt 
4
1.0:1.0:1.0:1.0
$ gcc multiplicacaoMatrizVetor.c 
$ ./a.out matriz.txt vetor.txt resultado.txt 
$ cat resultado.txt 
3
3.00:3.00:3.00
