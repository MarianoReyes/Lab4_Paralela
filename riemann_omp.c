/*
Codigo creado por
jose mariano reyes
20074
Programa para calcular el area bajo la curva paralelamente
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
// definición de la función f(x) que se va a integrar
double f(double x)
{
    return sin(x);
}
// función que calcula la aproximación del área bajo la curva usando la Regla del Trapecio
double trapezoides(double a, double b, int n)
{
    double h = (b - a) / n;
    double sum = 0.5 * (f(a) + f(b)); // primer y último término
    for (int i = 1; i < n; ++i)
    {
        double x = a + i * h;
        sum += f(x);
    }
    return h * sum;
}
int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Uso: %s a b <cantidad de threads>\n", argv[0]);
        return 1;
    }
    double a = atof(argv[1]);
    double b = atof(argv[2]);
    int num_threads = atoi(argv[3]);
    int n = 1000000; // valor de n
    double area = 0.0;
    double h = (b - a) / n;
#pragma omp parallel num_threads(num_threads) // paralelo
    {
        int ID_thread = omp_get_thread_num();
        int total_threads = omp_get_num_threads();
        int n_local = n / total_threads;
        double span = n_local * h;
        double offset = ID_thread * span;
        double a_local = a + offset;
        double b_local = a_local + span;
        double local_result = trapezoides(a_local, b_local, n_local);
#pragma omp critical
        {
            area += local_result;
        }
    }
    printf("Con n=%d trapezoides y %d threads, nuestra aproximación de la integral de %.2f a %.2f es = % .6f\n ", n, num_threads, a, b, area);
    return 0;
}