#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define CANT_EXPERIMENTO 100000
#define CANT_DIGITOS 3
#define MAX_NUMERO 9

/*

Preguntas teoricas del tp:

(e) ¿Sirve como metodo de busqueda de raıces?
(f) ¿Bajo que condiciones lo utilizarıa?
(g) ¿Serıa correcto hablar de convergencia?

e. Sí, el método de fuerza bruta consiste en probar una gran cantidad de valores en un rango específico para encontrar una raíz, 
sin embargo no es un metodo muy eficiente, en especial si se requiere un grado alto de precision de la raiz. 
f. Esto puede ser útil en algunos casos, especialmente si se sabe que la raíz se encuentra en un rango acotado y no hay otra 
información disponible o si se quiere buscar el intervalo donde cambia de signo la funcion. Sin embargo, en la mayoría de los casos,
hay métodos más precisos y eficientes para encontrar raíces. Por ejemplo, el método de bisección, el método de Newton-Raphson y 
el método de la secante son métodos numéricos que permiten encontrar raíces con mayor precisión y rapidez.
g. El método de fuerza bruta para buscar raíces no siempre converge, no siempre encuentra una solución y puede que nunca lo haga 
en algunos casos. En el caso que ni siquiera conozcamos que la raiz esta en un rango acotado o que este sea muy grande, puede llevar 
mucho tiempo probar todas las combinaciones posibles, lo que puede no ser practico o incluso imposible en algunos casos. Tambien pueden 
ocurrir errores que al tratar de hallar una raiz, tomemos como criterio que a determinado valor muy chico, lo consideremos como la raiz. 
Pero tranquilamente la funcion puede tomar valores cercanos al cero, y jamas cortar el eje x.



(a) Definir un numero entero de 3 dıgitos al azar a traves de la funcion random, simulando la
    clave de un candado.
*/
//devuelve un vector de 3 numeros random
int* generar_clave_aleatoria() 
{
    int primer_digito = rand() % 10;
    int segundo_digito = rand() % 10;
    int tercer_digito = rand() % 10;

    int* clave = (int*) malloc(CANT_DIGITOS * sizeof(int));
    clave[0] = primer_digito;
    clave[1] = segundo_digito;
    clave[2] = tercer_digito;

    return clave;
}
/*

(b) Programar un algoritmo de fuerza bruta para hallar la clave.

*/
//Implementa el algoritmo fuerza bruta para una clave almacenada en un vector de 3 posiciones
void algoritmo_fuerza_bruta(FILE *outputfile, int intento)
{
    int* clave = generar_clave_aleatoria();

    printf("La clave es %i%i%i\n", clave[0], clave[1], clave[2]);

    int cantidad_iteraciones = 0;
    bool encontrado = false;


    for (int i = 0; i <= MAX_NUMERO && !encontrado; i++){;

         for(int j = 0; j <= MAX_NUMERO && !encontrado; j++){;

             for(int k = 0; k <= MAX_NUMERO && !encontrado; k++){;

                cantidad_iteraciones++;
                 if(clave[0] == i && clave[1] == j && clave[2] == k)
                    encontrado = true;
             }
        }
    }

    int m, claveint = 0;
    for (m = 0; m < 3; m++){
        claveint = 10 * claveint + clave[m];
    }

	printf ("Se realizaron %i iteraciones\n\n", cantidad_iteraciones);
    fprintf(outputfile,"%d;%d;%d\n", intento, claveint, cantidad_iteraciones);

}


/*

(c) Realizar el experimento al menos 100000 veces, anotando la cantidad de intentos realizados
hasta hallar la respuesta.
(d) Realizar un histograma para graficar los intentos. Las columnas del histograma seran separadas en 0-10, 10-20, 20-30, etc...

*/
void realizar_experimento(FILE* outputfile)
{
    for (int i = 0; i <= CANT_EXPERIMENTO; i++)
        algoritmo_fuerza_bruta(outputfile, i);

}

int main() 
{
    srand(time(NULL));

    FILE *outputfile = fopen("output/fuerzabruta.csv", "w");
    fprintf(outputfile, "#;Clave;Intentos\n");
    realizar_experimento(outputfile);
    fclose(outputfile);

    return 0;
}