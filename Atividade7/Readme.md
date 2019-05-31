Objetivo
Desenvolver um programa paralelo que faça o cálculo da integral de uma função usando o método do trapézio.

Código Serial
Considere o seguinte código serial que implementa o cálculo da integral de uma função usando o método do trapézio:

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double x) {
  double return_val = 0.0;
  // return_val = x*x*x*x - x*x*x + x*x - x + 1;
  return_val = cos(x * log(1.0/x));
  return return_val;
}

int main(int argc, char *argv[]) {
  // Valor da integral
  double integral; 
  // Limites do intervalo
  double a, b;
  // Número de trapézios
  int n;
  // Base do trapézio
  double h;
  double x;
  int i;

  a = atof(argv[1]);
  b = atof(argv[2]);
  n = atoi(argv[3]);

  h = (b - a) / n;
  integral = (f(a) + f(b))/2.0;

  x = a;

  for (i = 1; i < n; i++) {
   x += h;
   integral += f(x);
  }

  integral *= h;
  printf("%d trapézios, estimativa de %.2f a %.2f = %.5f\n", n, a, b, integral);

  return 0;
}
Esse programa recebe três parâmetros:

O início do intervalo a ser guardado na variável a.
O fim do intervalo a ser guardado na variável b.
A precisão, ou número de trapézios, a ser guardada na variável n.
Considerando que o código acima está guardado no arquivo serial.c, a execução se daria da seguinte forma:

$ gcc serial.c -o serial -lm
$ time ./serial 1.0 10000.0 80000000
80000000 trapézios, estimativa de 1.00 a 10000.00 = 0.11515

real  0m5.1
user  0m5.1
sys   0m0.0
Nós estamos prefixando a execução do programa com o comando time para medir o tempo de execução. O que nos interessa é o valor do campo real, neste caso 5,1 segundos.

Código Paralelo
Sua missão é paralelizar o código acima e guardar o resultado no arquivo paralelo.c na pasta atividades/atividade07. Para testar verifique se os resultados são os mesmos em ambas as versões serial e paralela, dados os mesmos parâmetros. Uma pequena diferença, até às duas últimas cadas decimais, é aceitável. Seu código paralelo precisa ser mais rápido que o serial, sendo que você está livre para usar qualquer operação do MPI. Para medir, considere o seguinte teste:

$ mpicc paralelo.c -o paralelo -lm
$ time mpirun -np 8 ./paralelo 1.0 10000.0 80000000 
80000000 trapézios, estimativa de 1.00 a 10000.00 = 0.11515

real	0m1.092s
user	0m6.977s
sys	0m0.218s
Lembre-se que função usada não está definida para todos os intervalos, portanto alguns testes com valores diferentes de a e b podem retornar valores inválidos.
