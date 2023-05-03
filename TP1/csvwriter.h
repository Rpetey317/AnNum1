//
// Created by rpetey317 on 5/3/23.
//

#ifndef ANNUM1_CSVWRITER_H
#define ANNUM1_CSVWRITER_H

#include "stdio.h"
#include "rootfinding.h"

/*
 alpha = log|(x_n+1 - x_n)/(x_n - x_n-1)|/
         log|(x_n - x_n-1)/(x_n-1 - x_n-2)|
 */

void escribirBiseccion(raiz_t *raiz, char* filename)
{
    FILE *file = fopen(filename, "w");
    double alpha, lambda;
    double x_np1, x_n, x_nm1, x_nm2;

    for (int i = 0; i < raiz->size_iteraciones; i++) {
        x_np1 = raiz->iteraciones[i+1];
        x_n = raiz->iteraciones[i];
        x_nm1 = raiz->iteraciones[i-1];
        x_nm2 = raiz->iteraciones[i-2];

        alpha = (log(fabs((x_np1 - x_n)/(x_n - x_nm1))))/(log(fabs((x_n - x_nm1)/(x_nm1 - x_nm2))));
        lambda = (fabs(x_np1 - x_n))/(pow(fabs(x_n - x_nm1), alpha));

        fprintf(file, "");
    }
    fprintf(file, "");

    fclose(file);
}

#endif //ANNUM1_CSVWRITER_H
