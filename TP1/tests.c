#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "rootfinding.h"

double bisect(double x){
    return 3*x*x - 20*x + 7;
}

double ptofijofunc(double x){
    return (x*x)/4 - sin(x);
}

double funcionraicesmultiples(double x){
    return 4*(x - 0.26)*(x - 0.26)*(x - 0.26);
    // raiz en 0.26
}

double deriv1(double x){
    return 12*(x - 0.26)*(x - 0.26);
}

double deriv2(double x){
    return 24*(x - 0.26);
}

double secfunc(double x){
    return log(x) - 1;
}

int main() {

    const double intervalobis[] = {0.0, 1.0};
    raiz_t *raizbis = malloc(sizeof(raiz_t));

    const double intervalopf[] = {1.5, 2.0};
    raiz_t *raizpf = malloc(sizeof(raiz_t));

    double semillanr = 3.1;
    raiz_t *raiznr = malloc(sizeof(raiz_t));

    const double intervalosec[] = {2.5, 3.0};
    raiz_t *raizsec = malloc(sizeof(raiz_t));

    double semillanrm = 0.2;
    raiz_t *raiznrm = malloc(sizeof(raiz_t));

    biseccion(raizbis, bisect, intervalobis,
              10, DEFAULT_ERR, DEFAULT_ERR);

    ptofijo(raizpf, ptofijofunc, intervalopf,
              10, DEFAULT_ERR, DEFAULT_ERR);

    newtonRaphson(raiznr, sin, cos, semillanr,
                  10, DEFAULT_ERR, DEFAULT_ERR);

    secante(raizsec, secfunc, intervalosec,
            10, DEFAULT_ERR, DEFAULT_ERR );

    newtonRaphsonMod(raiznrm, funcionraicesmultiples, deriv1, deriv2, semillanrm,
                     10, DEFAULT_ERR, DEFAULT_ERR);


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

    printf("método Newton-Raphson:\n");
    printf("||p: %f||, f(p): %f, it: %d, errA: %f, errR: %f\n\n",
           raiznr->valor,
           raiznr->f_valor,
           raiznr->iteraciones,
           raiznr->absErr,
           raiznr->relErr);

    printf("método secante:\n");
    printf("||p: %f||, f(p): %f, it: %d, errA: %f, errR: %f\n\n",
           raizsec->valor,
           raizsec->f_valor,
           raizsec->iteraciones,
           raizsec->absErr,
           raizsec->relErr);

    printf("método N-R Mod:\n");
    printf("||p: %f||, f(p): %f, it: %d, errA: %f, errR: %f\n\n",
           raiznrm->valor,
           raiznrm->f_valor,
           raiznrm->iteraciones,
           raiznrm->absErr,
           raiznrm->relErr);

    free(raizbis);
    free(raizpf);
    free(raiznr);
    free(raizsec);
    free(raiznrm);

    return 0;
}
