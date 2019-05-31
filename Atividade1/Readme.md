O objetivo desta atividade é garantir que todos têm acesso ao servidor e conseguem compilar e executar programas em C. A primeira coisa que você irá fazer é criar um diretório atividades e um subdiretório atividade01.

$ mkdir atividades
$ mkdir atividades/atividade01
Dentro de atividade01, coloque o arquivo pi.c. Este programa deverá aproximar o valor de π através do método de Monte Carlo. Você pode considerar o seguinte algoritmo:

01. monteCarloPi(n) 
02. |  acertos ← 0 
03. |  para i ← 0 até n 
04. |  |  x ← sorteie um número real entre 0 e 1 
05. |  |  y ← sorteie um número real entre 0 e 1 
06. |  |  se(x * x + y * y < 1) 
07. |  |  |  acertos ← acertos + 1 
08. |  |  fim_se 
09. |  fim_para 
10. |  retorne 4 * acertos / n 11. fim_monteCarloPi
O seu programa deve ser invocado passando o valor de n (número de iterações) como parâmetro, exibindo o valor de π com até 5 casas de precisão:

$ cd atividades/atividade01
$ gcc pi.c -o pi
$ ./pi 100
pi = 3,15587
$ ./pi 500
pi = 3,14609
Não vamos explorar paralelismo neste primeiro momento. Mas o bom desse exemplo é que ele pode ser usado quando iniciarmos a programação paralela.
