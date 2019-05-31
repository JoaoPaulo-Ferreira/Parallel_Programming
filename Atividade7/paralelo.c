#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <mpi/mpi.h>

double f(double x) {
   double return_val = 0.0;
   // return_val = x*x*x*x - x*x*x + x*x - x + 1;
   return_val = cos(x * log(1.0/x));
   return return_val;
}

double calculaTrap(double a, double b, int n){
   int i;
   double h, x, integral;
   h = (b - a) / n;
   integral = (f(a) + f(b))/2.0;
   x = a;
   for (i = 1; i < n; i++) {
      x += h;
      integral += f(x);
   }
   return integral*h;
}

int main(int argc, char *argv[]) {
   int rank, size, vetorTamanho;
   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &size);
   // Valor da integral
   double integral, intervalo, resultado; 
   // Limites do intervalo
   double a, b, *final;
   // Número de trapézios
   int n;
   // Base do trapézio
   double h;
   double x;
   int i;

   if(rank == 0 ){
      a = atof(argv[1]);
      b = atof(argv[2]);
      n = atoi(argv[3]);
      n = n/size;
      intervalo = (b-a)/size;
      final = malloc(size*sizeof(double));
   }
      MPI_Bcast(&a, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
      MPI_Bcast(&intervalo, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
      MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
      a = a + (rank * intervalo);
      b = a + intervalo;
      integral = calculaTrap(a,b,n);
      MPI_Gather(&integral, 1, MPI_DOUBLE, final, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
      if (rank == 0){
         integral = 0;
         for(int i = 0; i < size; i++)
            integral += final[i];
         printf("%d trapézios, estimativa de %.2f a %.2f = %.5f\n", atoi(argv[3]), a, atof(argv[2]), integral);
      }
      MPI_Finalize();
   return 0;
}