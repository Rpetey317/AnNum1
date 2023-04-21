//
// Created by ruben on 20-Apr-23.
//

#include "rootfinding.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

raiz_t *biseccion(raiz_t *raiz, double (*func)(double), const double intervalo[2], int iteraciones, double maxAbsErr,
                  double maxRelErr, bool conPrint) {

    if (intervalo[0] > intervalo[1] || !raiz){
        return NULL;
    }

    bool condAbsErr = true, condRelErr = true;
    double absErr = DEFAULT_ERR, relErr = DEFAULT_ERR;
    int maxIter = (iteraciones < DEFAULT_IT) ? iteraciones : DEFAULT_IT;
    int i = 0;
    double p = (intervalo[1] - intervalo[0])/2, p_prev, a = intervalo[0], b = intervalo[1];

    while((i < maxIter) & condAbsErr & condRelErr){
        a = (func(b)*func(p) < 0) ? p : a;
        b = (func(a)*func(p) < 0) ? p : b;
        p_prev = p;
        p = (a+b)/2;

        absErr = fabs(p - p_prev);
        relErr = fabs(absErr/p);

        i++;
        condAbsErr = (maxAbsErr == DEFAULT_ERR) ? true : absErr > maxAbsErr;
        condRelErr = (maxRelErr == DEFAULT_ERR) ? true : relErr > maxRelErr;
    }

    raiz->iteraciones = i;
    raiz->absErr = absErr;
    raiz->relErr = relErr;
    raiz->valor = p;
    raiz->f_valor = func(p);

    return raiz;
}

raiz_t *ptofijo(raiz_t *raiz, double (*func)(double), const double intervalo[2], int iteraciones, double maxAbsErr,
                double maxRelErr, bool conPrint) {
    if (intervalo[0] > intervalo[1] || !raiz){
        return NULL;
    }

    bool condAbsErr = true, condRelErr = true;
    double absErr = DEFAULT_ERR, relErr = DEFAULT_ERR;
    int maxIter = (iteraciones < DEFAULT_IT) ? iteraciones : DEFAULT_IT;
    int i = 0;
    double p = (intervalo[1] - intervalo[0])/2, p_prev;

    while((i < maxIter) & condAbsErr & condRelErr){
        p_prev = p;
        p = p - func(p);

        absErr = fabs(p - p_prev);
        relErr = fabs(absErr/p);

        i++;
        condAbsErr = (maxAbsErr == DEFAULT_ERR) ? true : absErr > maxAbsErr;
        condRelErr = (maxRelErr == DEFAULT_ERR) ? true : relErr > maxRelErr;
    }

    raiz->iteraciones = i;
    raiz->absErr = absErr;
    raiz->relErr = relErr;
    raiz->valor = p;
    raiz->f_valor = func(p);

    return raiz;
}

