#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "src\rootfinding.h"

double funcion(double x){
    return 3*x*x - 20*x + 7;
}

double otrafuncion(double x){
    return (x*x)/4 - sin(x);
}

int main() {

    const double intervalo1[] = {0.0, 1.0};
    const double intervalo2[] = {1.5, 2.0};
    raiz_t *raizbis = malloc(sizeof(raiz_t));
    raiz_t *raizpf = malloc(sizeof(raiz_t));

    biseccion(raizbis, funcion, intervalo1,
              100, DEFAULT_ERR, DEFAULT_ERR, false);

    ptofijo(raizpf, otrafuncion, intervalo2,
              100, DEFAULT_ERR, DEFAULT_ERR, false);

    printf("método bisección:\n");
    printf("||p: %f||, f(p): %f, it: %d, errA: %f, errR: %f\n\n",
            raizbis->valor,
            raizbis->f_valor,
            raizbis->iteraciones,
            raizbis->absErr,
            raizbis->relErr);

    printf("método pto. fijo:\n");
    printf("||p: %f||, f(p): %f, it: %d, errA: %f, errR: %f\n\n",
           raizpf->valor,
           raizpf->f_valor,
           raizpf->iteraciones,
           raizpf->absErr,
           raizpf->relErr);

    return 0;
}
