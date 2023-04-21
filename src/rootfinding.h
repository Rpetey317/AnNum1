//
// Created by ruben on 20-Apr-23.
//

#ifndef ANNUM1_ROOTFINDING_H
#define ANNUM1_ROOTFINDING_H

#include <stdbool.h>

#define DEFAULT_ERR -1.0
#define DEFAULT_IT 100000

typedef struct raiz{
    double valor;
    double f_valor;
    double absErr;
    double relErr;
    int iteraciones;
} raiz_t;

/*
 * Busca la raíz de la funcion en el intervalo indicado por biseccion.
 * Corre hasta obtener un error menor al medido, o hasta alcanzar las iteraciones
 * indicadas, o por 100000 iteraciones, lo que pase primero
 * pasar DEFAULT_ERR como parámetro a los errores para ignorarlos.
 * Devuelve NULL si el intervalo es vacío
 */
raiz_t *biseccion(raiz_t *raiz, double (*func)(double), const double intervalo[2], int iteraciones, double maxAbsErr,
                  double maxRelErr, bool conPrint);

/*
 * Busca la raíz de la funcion en el intervalo indicado por punto fijo.
 * Corre hasta obtener un error menor al medido, o hasta alcanzar las iteraciones
 * indicadas, o por 100000 iteraciones, lo que pase primero
 * pasar DEFAULT_ERR como parámetro a los errores para ignorarlos.
 * Devuelve NULL si el intervalo es vacío
 */
raiz_t *ptofijo(raiz_t *raiz, double (*func)(double), const double intervalo[2], int iteraciones, double maxAbsErr,
                double maxRelErr, bool conPrint);

#endif //ANNUM1_ROOTFINDING_H
