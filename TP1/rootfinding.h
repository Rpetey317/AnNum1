//
// Created by ruben on 30-Apr-23.
//

#ifndef ANNUM1_ROOTFINDING_H
#define ANNUM1_ROOTFINDING_H

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define DEFAULT_ERR -1.0
#define DEFAULT_IT 100000

typedef struct raiz{
    double valor;
    double f_valor;
    double absErr;
    double relErr;
    double *iteraciones;
    size_t size_iteraciones;
} raiz_t;

raiz_t *biseccion(raiz_t *raiz, double (*func)(double), const double intervalo[2], int iteraciones, double maxAbsErr,
                  double maxRelErr) {

    if (intervalo[0] > intervalo[1] || !raiz){
        return NULL;
    }

    bool condAbsErr = true, condRelErr = true;
    double absErr = DEFAULT_ERR, relErr = DEFAULT_ERR;
    int maxIter = (iteraciones < DEFAULT_IT) ? iteraciones : DEFAULT_IT;
    int i = 0;
    double p = (intervalo[1] - intervalo[0])/2, p_prev, a = intervalo[0], b = intervalo[1];
    raiz->iteraciones = calloc(iteraciones, sizeof(double));

    while((i < maxIter) & condAbsErr & condRelErr){
        a = (func(b)*func(p) < 0) ? p : a;
        b = (func(a)*func(p) < 0) ? p : b;
        p_prev = p;
        p = (a+b)/2;

        absErr = fabs(p - p_prev);
        relErr = fabs(absErr/p);

        raiz->iteraciones[i] = p;
        i++;
        condAbsErr = (maxAbsErr == DEFAULT_ERR) ? true : absErr > maxAbsErr;
        condRelErr = (maxRelErr == DEFAULT_ERR) ? true : relErr > maxRelErr;
    }

    raiz->size_iteraciones = i;
    raiz->absErr = absErr;
    raiz->relErr = relErr;
    raiz->valor = p;
    raiz->f_valor = func(p);

    return raiz;
}

raiz_t *ptofijo(raiz_t *raiz, double (*func)(double), const double intervalo[2], int iteraciones, double maxAbsErr,
                double maxRelErr) {
    if (intervalo[0] > intervalo[1] || !raiz){
        return NULL;
    }

    bool condAbsErr = true, condRelErr = true;
    double absErr = DEFAULT_ERR, relErr = DEFAULT_ERR;
    int maxIter = (iteraciones < DEFAULT_IT) ? iteraciones : DEFAULT_IT;
    int i = 0;
    double p = (intervalo[1] - intervalo[0])/2, p_prev;
    raiz->iteraciones = calloc(iteraciones, sizeof(double));

    while((i < maxIter) & condAbsErr & condRelErr){
        p_prev = p;
        p = p - func(p);

        absErr = fabs(p - p_prev);
        relErr = fabs(absErr/p);

        raiz->iteraciones[i] = p;
        i++;
        condAbsErr = (maxAbsErr == DEFAULT_ERR) ? true : absErr > maxAbsErr;
        condRelErr = (maxRelErr == DEFAULT_ERR) ? true : relErr > maxRelErr;
    }

    raiz->size_iteraciones = i;
    raiz->absErr = absErr;
    raiz->relErr = relErr;
    raiz->valor = p;
    raiz->f_valor = func(p);

    return raiz;
}

raiz_t *newtonRaphson(raiz_t *raiz, double (*func)(double), double (*derivada)(double), double semilla,
                      int iteraciones, double maxAbsErr, double maxRelErr) {

    bool condAbsErr = true, condRelErr = true;
    double absErr = DEFAULT_ERR, relErr = DEFAULT_ERR;
    int maxIter = (iteraciones < DEFAULT_IT) ? iteraciones : DEFAULT_IT;
    int i = 0;
    double p = semilla, p_prev;
    raiz->iteraciones = calloc(iteraciones, sizeof(double));

    while((i < maxIter) & condAbsErr & condRelErr){
        p_prev = p;
        p = p - (func(p)/derivada(p));

        absErr = fabs(p - p_prev);
        relErr = fabs(absErr/p);

        raiz->iteraciones[i] = p;
        i++;
        condAbsErr = (maxAbsErr == DEFAULT_ERR) ? true : absErr > maxAbsErr;
        condRelErr = (maxRelErr == DEFAULT_ERR) ? true : relErr > maxRelErr;
    }

    raiz->size_iteraciones = i;
    raiz->absErr = absErr;
    raiz->relErr = relErr;
    raiz->valor = p;
    raiz->f_valor = func(p);

    return raiz;
}

raiz_t *newtonRaphsonMod(raiz_t *raiz, double (*func)(double), double (*deriv1)(double), double (*deriv2)(double),
                         double semilla, int iteraciones, double maxAbsErr, double maxRelErr) {

    bool condAbsErr = true, condRelErr = true;
    double absErr = DEFAULT_ERR, relErr = DEFAULT_ERR;
    int maxIter = (iteraciones < DEFAULT_IT) ? iteraciones : DEFAULT_IT;
    int i = 0;
    double p =  semilla, p_prev;
    raiz->iteraciones = calloc(iteraciones, sizeof(double));

    while((i < maxIter) & condAbsErr & condRelErr){
        p_prev = p;
        p = p - ((func(p)*deriv1(p)) / (deriv1(p)*deriv1(p) - func(p)*deriv2(p)));

        absErr = fabs(p - p_prev);
        relErr = fabs(absErr/p);

        raiz->iteraciones[i] = p;
        i++;
        condAbsErr = (maxAbsErr == DEFAULT_ERR) ? true : absErr > maxAbsErr;
        condRelErr = (maxRelErr == DEFAULT_ERR) ? true : relErr > maxRelErr;
    }

    raiz->size_iteraciones = i;
    raiz->absErr = absErr;
    raiz->relErr = relErr;
    raiz->valor = p;
    raiz->f_valor = func(p);

    return raiz;
}

raiz_t *secante(raiz_t *raiz, double (*func)(double), const double semillas[2], int iteraciones, double maxAbsErr,
                double maxRelErr) {
    if (semillas[0] > semillas[1] || !raiz){
        return NULL;
    }

    bool condAbsErr = true, condRelErr = true;
    double absErr = DEFAULT_ERR, relErr = DEFAULT_ERR;
    int maxIter = (iteraciones < DEFAULT_IT) ? iteraciones : DEFAULT_IT;
    int i = 0;
    double p = semillas[0], p_prev1 = semillas[1] , p_prev2;
    raiz->iteraciones = calloc(iteraciones, sizeof(double));

    while((i < maxIter) & condAbsErr & condRelErr){
        p_prev2 =p_prev1;
        p_prev1 = p;
        p = p_prev1 - ((func(p_prev1)*(p_prev1 - p_prev2))/(p_prev1 - p_prev2));

        absErr = fabs(p - p_prev1);
        relErr = fabs(absErr/p);

        raiz->iteraciones[i] = p;
        i++;
        condAbsErr = (maxAbsErr == DEFAULT_ERR) ? true : absErr > maxAbsErr;
        condRelErr = (maxRelErr == DEFAULT_ERR) ? true : relErr > maxRelErr;
    }

    raiz->size_iteraciones = i;
    raiz->absErr = absErr;
    raiz->relErr = relErr;
    raiz->valor = p;
    raiz->f_valor = func(p);

    return raiz;
}


#endif //ANNUM1_ROOTFINDING_H
