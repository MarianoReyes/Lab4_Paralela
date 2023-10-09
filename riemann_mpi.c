/*
Codigo creado por
jose mariano reyes
20074
Programa para calcular el area bajo la curva
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

// Definición de la función f(x) que se va a integrar
double f(double x)
{
    // Cambiar esta función para las diferentes corridas y compilar
    return sin(x);
}

// Función que calcula la aproximación del área bajo la curva usando la regla del trapecio
double trapezoides(double a, double b, int n, double h)
{
    double sum = 0.5 * (f(a) + f(b)); // Primer y último término
    for (int i = 1; i < n; ++i)
    {
        double x = a + i * h;
        sum += f(x);
    }
    return h * sum;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Uso: %s a b\n", argv[0]);
        return 1;
    }

    MPI_Init(&argc, &argv);

    double a = atof(argv[1]);
    double b = atof(argv[2]);
    int n = 1000000; // Valor de n
    double h = (b - a) / n;

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int local_n = n / size;
    double local_a = a + rank * local_n * h;
    double local_b = local_a + local_n * h;

    double local_result = trapezoides(local_a, local_b, local_n, h);
    double total_result;

    MPI_Reduce(&local_result, &total_result, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        printf("Con n=%d trapezoides, nuestra aproximación de la integral de %.2f a %.2f es = %.6f\n", n, a, b, total_result);
    }

    MPI_Finalize();
    return 0;
}
