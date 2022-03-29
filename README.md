# Matrix_Multiplication_Pthreads
Programa modular en en lenguaje de programación C, que realiza la multiplicación de matrices NxN utilizando hilos, de tal manera que el procesamiento sea secuencial.

A continuación se presenta la manera en la que se ejecutan los scripts correspondientes:

1. Eliminar archivos compilados anteriormente

    ```bash
    user@user:~$ make clean
    ```
2. Compilar el programa para generar el ejecutable

    ```bash
    user@user:~$ make
    ```
3. Ejecutar el programa, los argumentos corresponden a la cantidad de hilos y el tamaño de la matriz (NxN)

    ```bash
    user@user:~$ ./MMPosix <matrix size> <number of threads>
    ```
