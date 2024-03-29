#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rootfinding.h"

// Funciones a estudiar
double f1(double x)
{
    return (pow(x, 3) - 19);
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

// Funciones modificadas para pto fijo
double g1(double x)
{
    return x- f1(x)/(27);
}

double g2(double x)
{
    return x - f2(x)/(-13.6715);
}

double g3(double x)
{
    return x - f3(x)/(0.9);
}

void imprimir_raices(raiz_t *raiz, char* metodo)
{
    printf("Método %s:\n", metodo);
    printf("||p: %.15f||, it: %zu, errA: %.15f, errR: %.15f\n\n",
            raiz->valor,
            raiz->size_iteraciones,
            raiz->absErr,
            raiz->relErr);
}

void estudiar_funciones(double tolerancia, double (*f)(double), double (*deriv1)(double), double (*deriv2)(double),
                        double (*gx)(double), double x_real, const char *prefix, const double *intervalo, double semillanr)
{
    int strsize = 40;
    char *filename = calloc(strsize, sizeof(char));

    //bissección
    raiz_t *raizbis = malloc(sizeof(raiz_t));
    biseccion(raizbis, f, intervalo, tolerancia);
    imprimir_raices(raizbis, "Biseccion");
    memset(filename, '\0', strsize);
    strcpy(filename, prefix);
    strcat(filename, "biseccion.csv");
    escribirRaizAArchivo(raizbis, x_real, filename);

    double seed = raizbis->iteraciones[1];

    //Punto fijo
    raiz_t *raizpf = malloc(sizeof(raiz_t));
    ptofijo(raizpf, gx, seed, tolerancia);
    imprimir_raices(raizpf, "Punto Fijo");
    memset(filename, '\0', sizeof(strsize));
    strcpy(filename, prefix);
    strcat(filename, "ptofijo.csv");
    escribirRaizAArchivo(raizpf, x_real, filename);

    //Newton-Raphson
    raiz_t *raiznr = malloc(sizeof(raiz_t));
    newtonRaphson(raiznr, f, deriv1, semillanr, tolerancia);
    imprimir_raices(raiznr, "Newton-Raphson");
    memset(filename, '\0', sizeof(strsize));
    strcpy(filename, prefix);
    strcat(filename, "newtonraphson.csv");
    escribirRaizAArchivo(raiznr, x_real, filename);
     
    //Secantes
    double secseeds[] = {raizbis->iteraciones[1], raizbis->iteraciones[2]};

    raiz_t *raizsec = malloc(sizeof(raiz_t));
    secante(raizsec, f, secseeds, tolerancia);
    imprimir_raices(raizsec, "Secante");
    memset(filename, '\0', sizeof(strsize));
    strcpy(filename, prefix);
    strcat(filename, "secantes.csv");
    escribirRaizAArchivo(raizsec, x_real, filename);

    //Newton-Raphson modificado
    raiz_t *raiznrm = malloc(sizeof(raiz_t));
    newtonRaphsonMod(raiznrm, f, deriv1, deriv2, semillanr, tolerancia);
    imprimir_raices(raiznrm, "N-R Mod");
    memset(filename, '\0', sizeof(strsize));
    strcpy(filename, prefix);
    strcat(filename, "nrmodificado.csv");
    escribirRaizAArchivo(raiznrm, x_real, filename);

    free(raizbis);
    free(raizpf);
    free(raiznr);
    free(raizsec);
    free(raiznrm);
    free(filename);
}

void analisis_adicional()
{
    double intervalo[] = {0.0, 3.0};

    raiz_t *raizbis = malloc(sizeof(raiz_t));
    biseccion(raizbis, f1, intervalo, 1e-5);
    double seed = raizbis->iteraciones[3];

    raiz_t *raiznr = malloc(sizeof(raiz_t));
    newtonRaphson(raiznr, f1, derivada_f1, seed, 1e-13);
    escribirRaizAArchivo(raiznr, cbrt(19.0), "output/extra_newRaph_f1_conBisDeArranque.csv");


    biseccion(raizbis, f2, intervalo, 1e-5);
    seed = raizbis->iteraciones[3];

    newtonRaphson(raiznr, f2, derivada_f2, seed, 1e-13);
    escribirRaizAArchivo(raiznr, 0.8049885393484, "output/extra_newRaph_f2_conBisDeArranque.csv");


    biseccion(raizbis, f3, intervalo, 1e-5);
    seed = raizbis->iteraciones[3];

    newtonRaphson(raiznr, f3, derivada_f3, seed, 1e-13);
    escribirRaizAArchivo(raiznr, 0.9, "output/extra_newRaph_f3_conBisDeArranque.csv");

    free(raizbis);
    free(raiznr);
}

int main(){

    double tolerancia1 = 1e-5;
    double tolerancia2 = 1e-13;
    double x_real_f1 = cbrt(19.0);
    double x_real_f2 = 0.8049885393484; //de WolframAlpha
    double x_real_f3 = 0.9;
    
    const double intervalo[] = {0.0, 3.0};
    const double intervalof2[] = {0.2, 0.9};
    double semillanr = 0.5;
    double semillanrf3 = 1.0;

    printf("==================================================\n");
    printf("==============PRIMER CRITERIO: 1E-5==============\n");
    printf("==================================================\n\n\n");

    printf("===F1===\n\n");
    estudiar_funciones(tolerancia1, f1, derivada_f1,
                       derivada2_f1, g1, x_real_f1, "output/f1-10e-05_", intervalo, semillanr);
    printf("===F2===\n\n");
    estudiar_funciones(tolerancia1, f2, derivada_f2,
                       derivada2_f2, g2, x_real_f2, "output/f2-10e-05_", intervalof2, semillanr);
    printf("===F3===\n\n");
    estudiar_funciones(tolerancia1, f3, derivada_f3,
                       derivada2_f3, g3, x_real_f3, "output/f3-10e-05_", intervalo, semillanrf3);

    printf("==================================================\n");
    printf("=============SEGUNDO CRITERIO: 10E-13=============\n");
    printf("==================================================\n\n\n");

    printf("===F1===\n\n");
    estudiar_funciones(tolerancia2, f1, derivada_f1,
                       derivada2_f1, g1, x_real_f1, "output/f1-10e-13_", intervalo, semillanr);
    printf("===F2===\n\n");
    estudiar_funciones(tolerancia2, f2, derivada_f2,
                       derivada2_f2, g2, x_real_f2, "output/f2-10e-13_", intervalof2, semillanr);
    printf("===F3===\n\n");
    estudiar_funciones(tolerancia2, f3, derivada_f3,
                       derivada2_f3, g3, x_real_f3, "output/f3-10e-13_", intervalo, semillanrf3);

    analisis_adicional();

    return 0;
}