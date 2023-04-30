#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double f1(double x) {
    return pow(x, 3) - 19;
}


/*

Defino esta funcion g para poder aplicar el algoritmo de punto fijo.
Lo que hice fue despejar x de la ecuacion x^3−19, y luego verificar si 
esta cumple con los teoremas del punto fijo (si se mapea sobre si misma
y si la derivada esta acotada entre 0 y 1)
... Pero no cumple :p estoy en eso

*/
double g(double x) {
    return pow(19, 1.0/3.0);
}

double metodo_biseccion(double a, double b, double epsilon, int* iteraciones)
{
    double p;

    while ((b-a) >= epsilon){
        p = (a + b) / 2;

        if (f1(p) == 0.0)
            break;
        
        if (f1(p) * f1(a) < 0)
            b = p;
        else
            a = p;
        
        (*iteraciones)++;
    }

    return p;
}

double metodo_punto_fijo(double semilla, double epsilon, int max_iteraciones) {
    double p0 = semilla;
    double p;
/*
    for(int i = 0; i < max_iteraciones; i++){
        p = g(p0);

        if ((fabs(p - p0) < epsilon))
            break;

        p0 = p;
    }
 */

    int i = 1;

    while (i <= max_iteraciones){
        p = g(p0);
        if (fabs(p - p0) < epsilon)
            return p;
        
        i++;
        p0 = p;
    }

    return p0;
}



int main(){

    double a = 0.0, b = 3.0, epsilon = 1e-5;
    int iteraciones = 0;
    double raiz_biseccion = metodo_biseccion(a, b, epsilon, &iteraciones);

    printf("== METODO BISECCION F1 ==\n");

    printf("La raíz aproximada es: %lf\n"
            "Se realizaron %i iteraciones\n", raiz_biseccion, iteraciones);
    

    /*
    double p0 = (b-a) / 2;
    double K = 1;
    int max_iteraciones = log(K / epsilon) / log(fabs(g(b) - g(a)));

    printf("== METODO PUNTO FIJO F1 ==\n");

    //double raiz_pto_fijo = metodo_punto_fijo(p0, epsilon, )
    */


    return 0;
}