#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "rootfinding.h"

// Funciones a estudiar
double f1(double x)
{
    return (x*x*x -19);
}
double derivada_f1(double x)
{
    return (3*x*x);
}
double derivada2_f1(double x)
{
    return (6*x);
}

double f2(double x)
{
    return (pow(x, 5) - (7.3)*pow(x, 4) + (2.24)*pow(x, 3) + (30.106)*pow(x, 2) - (42.1)*x + 15.94);
}
double derivada_f2(double x)
{
    return (5*pow(x, 4) - 29.2*pow(x, 3) + 6.72*pow(x, 2) + 60.212*x - 42.1);
}
double derivada2_f2(double x)
{
    return (20*pow(x, 3) - 87.6*pow(x, 2) + 13.44*x + 60.212);
}

double f3(double x)
{
    return (x - 0.9) * exp(-4 * pow(x - 0.9, 2));
}

double derivada_f3(double x)
{
    return ((-8 * x + 7.2) * (x - 0.9) + 1) * exp(-4 * pow(x - 0.9, 2));
}
double derivada2_f3(double x)
{
    return 64 * (-0.3915 + 2.055 * x - 2.7 * pow(x, 2) + pow(x, 3)) * exp(-4 * pow(x - 0.9, 2));
}

// funciones modificadas para pto fijo
double g1(double x)
{
    return f1(x)/27.0;
}

double g2(double x)
{
    return f2(x);
}

double g3(double x)
{
    return f3(x);
}

void imprimir_raices(raiz_t *raiz, char* metodo)
{
    printf("Método %s:\n", metodo);
    printf("||p: %f||, f(p): %f, it: %ld, errA: %f, errR: %f\n\n",
            raiz->valor,
            raiz->f_valor,
            raiz->size_iteraciones,
            raiz->absErr,
            raiz->relErr);
}

void estudiar_funciones(double epsilon, double (*func)(double),
                        double (*deriv1)(double), double (*deriv2)(double), double (*gx)(double))
{

    const double intervalo[] = {0.0, 3.0};
    double semillanr = 0.5;

    //bissección
    raiz_t *raizbis = malloc(sizeof(raiz_t));
    biseccion(raizbis, func, intervalo,
              DEFAULT_IT, epsilon, DEFAULT_ERR);
    imprimir_raices(raizbis, "Biseccion");

    //Punto fijo
    raiz_t *raizpf = malloc(sizeof(raiz_t));
    ptofijo(raizbis, gx, intervalo,
              DEFAULT_IT, epsilon, DEFAULT_ERR);
    imprimir_raices(raizbis, "Punto Fijo");

    //Newton-Raphson
    raiz_t *raiznr = malloc(sizeof(raiz_t));
    newtonRaphson(raiznr, func, deriv1, semillanr,
                  DEFAULT_IT, epsilon, DEFAULT_ERR);
    imprimir_raices(raiznr, "Newton-Raphson");
    
    //Secantes
    raiz_t *raizsec = malloc(sizeof(raiz_t));
    secante(raizsec, func, intervalo,
            DEFAULT_IT, epsilon, DEFAULT_ERR);
    imprimir_raices(raizsec, "Secante");

    //Newton-Raphson modificado
    raiz_t *raiznrm = malloc(sizeof(raiz_t));
    newtonRaphsonMod(raiznrm, func, deriv1, deriv2, semillanr,
                     DEFAULT_IT, epsilon, DEFAULT_ERR);
    imprimir_raices(raiznrm, "N-R Mod");

    free(raizbis);
    free(raizpf);
    free(raiznr);
    free(raizsec);
    free(raiznrm);

}

int main(){

    double primer_criterio_parada = 1e-5;
    double segundo_criterio_parada = 1e-13;

    printf("===F1===\n\n");
    estudiar_funciones(primer_criterio_parada, f1, derivada_f1, derivada2_f1, g1);
    printf("===F2===\n\n");
    estudiar_funciones(primer_criterio_parada, f2, derivada_f2, derivada2_f2, g2);
    printf("===F3===\n\n");
    estudiar_funciones(primer_criterio_parada, f3, derivada_f3, derivada2_f3, g3);

    return 0;
}