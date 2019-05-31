Objetivo
Praticar o uso das primitivas de comunicação ponto-a-ponto do MPI. Coloque o código dessa atividade na pasta atividades/atividade03.

Problema
Vamos transformar o programa da Atividade 01 em uma versão paralela. A diferença é que o cálculo do π deve ser distribuído entre vários processos MPI. A lógica do programa deve ser a seguinte:

Processo 0:

Recupera o parâmetro com o número de iterações a serem executadas.
Calcula quantas iterações deve executar a partir do valor do parâmetro e da quantidade de processos.
Realiza o cálculo local.
Recebe de cada um dos outros processos o valor calculado.
Adiciona sua contribuição local ao somatório dos resultados dos outros processos.
Imprime o valor calculado.
Processo i (i diferente de 0):

Recupera o parâmetro com o número de iterações a serem executadas.
Calcula quantas iterações deve executar a partir do valor do parâmetro e da quantidade de processos.
Realiza o cálculo local
Envia para o processo 0 sua contribuição.
Correção
A compilação do programa deve ser feita da seguinte forma:

$ mpicc pi.c -o pi

A execução tem essa sintaxe:

$ mpirun -np 2 ./pi 1000
pi = 3,142342
Você deve confirmar que o programa funciona para quantidades de processos iguais a 2, 4 e 8. Assuma que o número de iterações é divísivel pela quantidade de processos. Só use as diretivas ponto-a-ponto.
