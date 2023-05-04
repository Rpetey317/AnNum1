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

/*====================================================*/
// analisis de convergencia
double getAlpha(raiz_t *raiz, size_t indice)
{
    if(indice == 0 || indice == 1 || indice >= raiz->size_iteraciones - 1){
        return 0;
    }

    double x_np1, x_n, x_nm1, x_nm2;
    x_np1 = raiz->iteraciones[indice+1];
    x_n = raiz->iteraciones[indice];
    x_nm1 = raiz->iteraciones[indice-1];
    x_nm2 = raiz->iteraciones[indice-2];

    double numerador = log(fabs((x_np1 - x_n) / (x_n - x_nm1)));
    double denominador = log(fabs((x_n - x_nm1) / (x_nm1 - x_nm2)));

    return numerador / denominador;
}

double getLambda(raiz_t *raiz, size_t indice, double alpha)
{
    if(indice == 0 || indice == 1 || indice >= raiz->size_iteraciones - 1){
        return 0;
    }

    double x_np1, x_n, x_nm1, x_nm2;
    x_np1 = raiz->iteraciones[indice+1];
    x_n = raiz->iteraciones[indice];
    x_nm1 = raiz->iteraciones[indice-1];

    return (fabs(x_np1 - x_n)) / (pow(fabs(x_n - x_nm1), alpha));
}

void escribirRaizAArchivo(raiz_t *raiz, double x_real, char* filename)
{
    FILE *file = fopen(filename, "w");
    fprintf(file,
            "n;x_n;|x_n - x_n-1|;log(|x_n - x_n-1|);|x_n - x_r|;log(|x_n - x_r|);alpha;lambda\n");
    double alpha, lambda, itErr, absErr;

    for (int i = 0; i < raiz->size_iteraciones; i++) {
        alpha = getAlpha(raiz, i);
        lambda = getLambda(raiz, i, alpha);
        itErr = (i == 0 ? 0 : raiz->iteraciones[i] - raiz->iteraciones[i - 1]);
        absErr = fabs(raiz->iteraciones[i] - x_real);

        fprintf(file, "%d;%g;%g;%g;%g;%g;%g;%g\n",
                i+1,
                raiz->iteraciones[i],
                fabs(itErr),
                log10(fabs(itErr)),
                fabs(absErr),
                log10(fabs(absErr)),
                alpha,
                lambda);
    }

    fclose(file);
}

/*====================================================*/
// buúsqueda de raicíes
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
