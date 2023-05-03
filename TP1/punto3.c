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

void estudiar_funciones(double epsilon, double (*func)(double), double (*deriv1)(double), double (*deriv2)(double)){

    const double intervalo[] = {0.0, 3.0};
    raiz_t *raizbis = malloc(sizeof(raiz_t));

    biseccion(raizbis, func, intervalo,
              DEFAULT_IT, epsilon, epsilon);
    
    printf("método bisección:\n");
    printf("||p: %f||, f(p): %f, it: %ld, errA: %f, errR: %f\n\n",
            raizbis->valor,
            raizbis->f_valor,
            raizbis->size_iteraciones,
            raizbis->absErr,
            raizbis->relErr);

    double semillanr = 0.5;
    raiz_t *raiznr = malloc(sizeof(raiz_t));

    newtonRaphson(raiznr, func, deriv1, semillanr,
                  DEFAULT_IT, epsilon, epsilon);

    printf("método Newton-Raphson:\n");
    printf("||p: %f||, f(p): %f, it: %ld, errA: %f, errR: %f\n\n",
           raiznr->valor,
           raiznr->f_valor,
           raiznr->size_iteraciones,
           raiznr->absErr,
           raiznr->relErr);
    
    raiz_t *raizsec = malloc(sizeof(raiz_t));

    secante(raizsec, func, intervalo,
            DEFAULT_IT, epsilon, epsilon);

    printf("método secante:\n");
    printf("||p: %f||, f(p): %f, it: %ld, errA: %f, errR: %f\n\n",
           raizsec->valor,
           raizsec->f_valor,
           raizsec->size_iteraciones,
           raizsec->absErr,
           raizsec->relErr);

    raiz_t *raiznrm = malloc(sizeof(raiz_t));

    newtonRaphsonMod(raiznrm, func, deriv1, deriv2, semillanr,
                     DEFAULT_IT, epsilon, epsilon);

    printf("método N-R Mod:\n");
    printf("||p: %f||, f(p): %f, it: %ld, errA: %f, errR: %f\n\n",
           raiznrm->valor,
           raiznrm->f_valor,
           raiznrm->size_iteraciones,
           raiznrm->absErr,
           raiznrm->relErr);

    free(raizbis);
    free(raiznr);
    free(raizsec);
    free(raiznrm);

}

int main(){

    double primer_criterio_parada = 1e-5;
    double segundo_criterio_parada = 1e-13;

    estudiar_funciones(primer_criterio_parada, f1, derivada_f1, derivada2_f1);
    estudiar_funciones(primer_criterio_parada, f2, derivada_f2, derivada2_f2);
    estudiar_funciones(primer_criterio_parada, f3, derivada_f3, derivada2_f3);

    return 0;
}