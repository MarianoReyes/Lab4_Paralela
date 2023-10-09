/*
Codigo creado por
jose mariano reyes
20074
Programa para calcular el area bajo la curva
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// Definición de la función f(x) que se va a integrar
double f(double x)
{
    // cambiar esta funcion para las diferentes corridas y compilar
    return sin(x);
}
// función que calcula la aproximación del área bajo la curva usando la regla del trapecio
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
    if (argc != 3)
    {
        printf("Uso: %s a b\n", argv[0]);
        return 1;
    }
    double a = atof(argv[1]);
    double b = atof(argv[2]);
    int n = 1000000; // valor de n
    double area = trapezoides(a, b, n);
    printf("Con n=%d trapezoides, nuestra aproximación de la integral de %.2f a %.2f es = %.6f\n", n, a, b, area);
    return 0;
}