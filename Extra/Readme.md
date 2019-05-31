Objetivo
O objetivo dessa atividade é propor uma reorganização do código para auxiliar nas próximas atividades. Vocês tem liberdade de organizar o código como desejar. Entretanto, já devem ter observado que várias atividades envolvem a manipulação de matrizes no formato textual que descrevi na Atividade 02. O que proponho nesta atividade é a definição de funções para lidar com esses arquivos com maior facilidade.

O aluno que desenvolver esta atividade e reutilizar o código escrito nas próximas atividades que envolvam matrizes ganhará 1,0 ponto extra além dos 10 pontos que estão em jogo no segundo grupo de atividades.

Formato do Arquivos de Entrada e Saída
Como já discutido na Atividade 02, uma matriz com 3 linhas e 4 colunas seria assim representada:

3
4
1.0:1.0:1.0:1.0
1.0:1.0:1.0:1.0
1.0:1.0:1.0:1.0
Isto não será alterado. Agora no caso de um vetor, iremos alterar a representação para ficar uniforme. Por exemplo, um vetor de 4 elementos antes seria informado assim:

4
1.0:1.0:1.0:1.0
Veja que esse vetor pode ser imaginado como uma matriz. Os 4 elementos podem estar organizados em linhas ou colunas. Então as possíveis representações seriam:

4
1
1.0
1.0
1.0
1.0
Um vetor com 4 linhas e 1 coluna, ou:

1
4
1.0:1.0:1.0:1.0
Um vetor com 1 linha e 4 colunas. No caso da Atividade 02, teríamos que usar a segunda representação, pois trata-se de uma multiplicação de uma matriz 3x4 por outra matriz (que é um vetor) 4x1, resultando em um resultado (vetor) 3x1.

Organização do Código
A sugestão é que definam a seguinte função:

float *lerMatriz(FILE *arquivoMatriz, int *linhas, int *colunas);
Essa função irá receber o arquivo matriz, fazer a leitura da quantidade de linhas e colunas e armazenar as variáveis apontadas por linhas e colunas, além de retornar um ponteiro para a região da memória para qual a matriz foi lida. Estamos considerando a matriz organizada de forma linear na memória, por ordem de linha, ou seja, uma linha atrás da outra. Essa organização, além de otimizar o acesso a cache e memória principal, tem outra vantagem importante: lembrem que as primitivas do MPI enviam dados a partir de um endereço inicial e de um contador. Supõe-se que os dados estão de forma linha linear na memória. Com uma única chamada, se a matriz também está linear na memória, é possível enviar várias linhas.

Outra função seria:

void imprimirMatriz(float *m, int linhas, int colunas);
Para imprimir a matriz na tela. Importante para depuração. Para imprimir a matriz em um arquivo:

void escreverMatriz(char *nomeDoArquivo, float *m, 
          int linhas, int colunas);
Por último, a função:

void liberarMatriz(float *m);
Libera a memória utilizada pela matriz. Esse é a organização que fiz, mas óbvio, que tiver ideia melhor, pode ir adiante nela. Eu vi que na Atividade 02 alunos já separaram algumas funções em cabeçalhos e bibliotecas. Eu só quero guiar essa organização de forma a modularizar o interesse de interação com o sistema de arquivos nessas funções, que vocês possam nas próximas atividades que envolvam matrizes apenas reutilizar o código e manter o foco no paralelismo.

Resultado
Coloque na pasta atividades/atividade_extra a solução para o mesmo problema da Atividade 02, agora reorganizado da forma sugerida acima.
