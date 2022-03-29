#include "modulo.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <sys/time.h>
#include <errno.h>

struct timespec inicio, fin;

/* -------------------------------------Funciones ------------------------------------*/

#define DATA_SZ (1024 * 1024 * 64 * 3)

static double MEM_CHUNK[DATA_SZ];

int main(int argc, char *argv[])
{

	int N = (int)atof(argv[1]);

	double *Ma, *Mb, *Mr;
	Ma = MEM_CHUNK;
	Mb = Ma + N * N;
	Mr = Mb + N * N;

	initMatrix(N, Ma, Mb, Mr);
	sampleStart();
	matrixMultiplyMM1f(N, Ma, Mb, Mr);

	/*	printf("Ma\n");
		printMatrix(N, Ma);
		printf("Mb\n");
		printMatrix(N, Mb);
		printf("Mr\n");
		printMatrix(N, Mr);
	*/
	sampleEnd();
	return 0;
}
