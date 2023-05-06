#include <math.h>
#include <stdio.h>
#include "rootfinding.h"

#define MAX_ITERACIONES 50
#define TOLERANCIA_MAXIMA 1e-15 // 1* 10^(-15)

/**
(a) Programar un algoritmo para aproximar π utilizando la funcion sen(x) 
    con el metodo de Newton-Raphson, en funcion de x, que realice iteraciones 
    hasta alcanzar el limite de la herramienta utilizada.
*/

double funcion(double x) {
    return sin(x);
}
double derivada(double x) {
    return cos(x);
}

double metodo_Newton_Raphson(double (*funcion)(double), double (*derivada)(double), 
                             double x, double tolerancia, int* iteraciones) 
{
    double x_anterior;
    do {
        x_anterior = x;
        x = x - (funcion(x))/(derivada(x));
        (*iteraciones)++;
        if ((*iteraciones) > MAX_ITERACIONES) {
            printf("hubo un error, el metodo no convergió\n");
            return x;
        }
    } while (fabs(x - x_anterior) > tolerancia);
    
    return x;
}

double calcular_PI_con_Newton_Raphson() 
{
    double semilla = 2;
    int iteraciones = 0;
    double resultado = metodo_Newton_Raphson(funcion, derivada, semilla, TOLERANCIA_MAXIMA, &iteraciones);

    printf("el resultado en %i iteraciones fue: %.15f +- 1e-15\n", iteraciones, resultado);
    return resultado;
}


/*                                            
(b) Programar un algoritmo para aproximar π 
    utilizando la serie de Leibniz, en funcion de n. 
*/

//la serie de Leiniz converge a 'π/4'
double serie_de_Leibniz(int n) 
{
    double resultado = 0;
    for (int i = 0; i < n; i++)
    { 
        resultado += (pow(-1, i) / (2*i +1));
    }
    return resultado * 4.0;
}

double calcular_PI_con_Leibniz() {
    double resultado = 4 * serie_de_Leibniz(500);
    return resultado;
}

int main() 
{
/**
(c) Ejecutar los programas solicitados en a y b utilizando representacion de 
    punto flotante de 32 bits y comparar las respuestas obtenidas con
    n = 10, n = 100, n = 1000, n = 10000 y n = 100000.
*/
    printf("(C) PUNTO FLOTANTE 32 BITS\n");
    printf("----------------------------\n");

    float semilla = 2;
    float tolerancia = 1e-7;
    int iteraciones = 0;
    float resultado1 = metodo_Newton_Raphson(funcion, derivada, semilla, tolerancia, &iteraciones);
    printf("El resultado con Newton-Raphson en %i iteraciones fue: %.7f +- 1e-7\n", iteraciones, resultado1);

    printf("Usando la serie de Leibniz:\n");
    double resultado2;
    for (int i = 10; i <= 100000; i*=10) {
        resultado2 = serie_de_Leibniz(i);
        printf("Para n=%i => el resultado fue: %.7f\n", i, resultado2);
    }
    


/*
(d) Ejecutar los programas solicitados en a y b utilizando representacion de
    punto flotante de 64 bits y comparar las respuestas obtenidas con
    n = 10, n = 100, n = 1000, n = 10000 y n = 100000.
*/
    printf("\n\n==========(D) PUNTO FLOTANTE 64 BITS==========\n\n");

    double semilla2 = 2;
    double tolerancia2 = 1e-15;
    iteraciones = 0;
    double resultado3 = metodo_Newton_Raphson(funcion, derivada, semilla2, tolerancia2, &iteraciones);
    printf("el resultado con Newton-Raphson en %i iteraciones fue: %.15f +- 1e-15\n", iteraciones, resultado3);

    printf("usando la serie de Leibniz:\n");
    double resultado4;
    for (int i = 10; i <= 100000; i*=10) {
        resultado4 = 4 * serie_de_Leibniz(i);
        printf("n=%i => el resultado fue: %.15f\n", i, resultado4);
    }

/*
(e) (OPCIONAL) Ejecutar los programas solicitados en a y b con una calculadora 
    (aclarar marca y modelo) y comparar las respuestas obtenidas con 
    n = 10, n = 100, n = 1000, n = 10000 y n = 100000 
    (en caso de no alcanzar la memoria de la calculadora utilizar el maximo n posible).
*/
    //...


/*
(f) Representar las dos respuestas finales obtenidas (para n = 100000 y 
    el metodo de Newton Raphson) en c, d y e de manera de expresarlo 
    como π = ¯π + ∆π.
*/
    printf("\n\n(f) Representacion de PI\n");
    printf("----------------------------\n");

    printf("en (c)\n");
    printf("  π = %.7f +- 1e-7\n", resultado1);//con N-R
    float error = fabs(resultado2 - resultado1);
    printf("  π = %.5f +- %.5f\n", resultado2, error); //con Leibniz

    printf("en (d)\n");
    printf("  π = %.15f +- 1e-15\n", resultado4);//con N-R
    error = fabs(resultado4 - resultado3);
    printf("  π = %.5f +- %.5f\n", resultado4, error);//con Leibniz

/*

(g) ¿Podemos afirmar que para la computadora el numero π es una constante?

    El número π no puede ser representado de manera exacta en una computadora 
    por las limitaciones de la representación númerica en el hardware y el software; 
    las computadoras trabajan con una representación finita de números, por lo tanto, 
    sólo puede almacenar y calcular una aproximación de pi con una cierta cantidad 
    de dígitos.
    En muchos lenguajes de programación se puede usar la constante "pi" para representar 
    el número π. Sin embargo, lo que realmente se está utilizando es una aproximación 
    con una precisión determinada, y esta puede variar según el lenguaje de programación 
    y las bibliotecas matemáticas utilizadas. En el contexto de una computadora, el número 
    π puede considerarse una constante, en el sentido de que su valor no cambia durante 
    la ejecución de un programa.

*/

    return 0;
}















