/************************
 * Fecha
 * Autor: Miguel Guerrero
 * Materia
 * Tema: Implementación Posix (Library)
 * Programa Principal para multiplicar 2 matrices con variables GLOBALES
 * Se requiere que el diseño sea modular
 * El modulo implmenetará las funciones para el cáclculo del producto de la matrix:
 * 1. Creación de variables doble puntero para matrices principal GLOBALES
 * 2. Función reserva de memoria para las matrices de doble puntero
 * 3. Función de Inicialización de las matrices
 * 4. Función para el producto de las matrices
 * Se divide la matriz A por porciones, a ser enviadas a cada hilo
 * --> El número de hilos será enviado al ejecutar la dimensión de la matriz será enviada al ejecutar
 * 5. La dimensión de la matriz siempre será cuadrada (NxN)
 * 6. Se necesita función para impresión de matrices (doble puntero)
 */

#include "modulo.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

int main(int argc, char *argv[])
{

    struct arg_struct args;

    if (argc != 3)
    {
        printf("./MMPosix <matrix size> <# of threads>\n");
        return -1;
    }

    args.N = atof(argv[1]);
    args.Nthreads = atof(argv[2]);

    pthread_t *threads = (pthread_t *)malloc(args.N * sizeof(pthread_t));
    args.Ma = memReserve(args.N);
    args.Mb = memReserve(args.N);
    args.Mc = memReserve(args.N);
    initMatrix_DoublePointers(args.Ma, args.Mb, args.Mc, args.N);
    if (args.N < 4)
    {
        printf("Matriz A\n");
        printMatrix_DoublePointers(args.Ma, args.N);
        printf("Matriz B\n");
        printMatrix_DoublePointers(args.Mb, args.N);
    }
    sampleStart();
    for (int i = 0; i < args.Nthreads; ++i)
    {
        args.idThread = i;
        pthread_create(&threads[i], NULL, &multMM, (void *)&args);
    }
    for (int i = 0; i < args.Nthreads; ++i)
    {
        pthread_join(threads[i], NULL);
    }
    sampleEnd();
    free(threads);
    if (args.N < 4)
    {
        printf("Matriz C\n");
        printMatrix_DoublePointers(args.Mc, args.N);
    }

    return 0;
}
