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
void sampleStart()
{
	clock_gettime(CLOCK_MONOTONIC, &inicio);
}

void sampleEnd()
{
	clock_gettime(CLOCK_MONOTONIC, &fin);
	double totalTime;
	totalTime = (fin.tv_sec - inicio.tv_sec) * 1e9;
	totalTime = (totalTime + (fin.tv_nsec - inicio.tv_nsec)) * 1e-9;
	printf("%f\n", totalTime);
}

double randNumber()
{
	float min = 0.001, max = 9.999;
	static int first = -1;
	if (first == (first < 0))
	{
		srand(time(NULL) + getpid());
	}
	if (min >= max)
	{
		return errno = EDOM, NAN;
	}
	return min + (float)rand() / ((float)RAND_MAX / (max - min));
}

void initMatrix(int SZ, double *Ma, double *Mb, double *Mr)
{
	int i, j;
	for (i = 0; i < SZ; ++i)
	{
		for (j = 0; j < SZ; ++j)
		{
			Ma[j + i * SZ] = 3.0 * (i - j);
			Mb[j + i * SZ] = 2.8 * (j + i);
			Mr[j + i * SZ] = 0.0;
		}
	}
}

void printMatrix(int SZ, double *M)
{
	int i, j;
	for (i = 0; i < SZ; ++i)
	{
		for (j = 0; j < SZ; ++j)
		{
			printf("  %f  ", M[j + i * SZ]);
		}
		printf("\n");
	}
	printf("----------------------------");
	printf("\n");
}

void matrixMultiplyMM1c(int size, double *Ma, double *Mb, double *Mr)
{
	int i, j;
	for (i = 0; i < size; ++i)
	{
		for (j = 0; j < size; ++j)
		{
			double *pA, *pB;
			double sumaAuxiliar = 0.0;
			pA = Ma + (i * size);
			pB = Mb + j;
			for (int k = 0; k < size; ++k, pA++, pB += size)
			{
				sumaAuxiliar += (*pA * *pB);
			}
			Mr[i * size + j] = sumaAuxiliar;
		}
	}
}

void matrixMultiplyMM1f(int size, double *Ma, double *Mb, double *Mr)
{
	int i, j;
	for (i = 0; i < size; ++i)
	{
		for (j = 0; j < size; ++j)
		{

			double *pA, *pB;
			double sumaAuxiliar = 0.0;
			pA = Ma + (i * size);
			pB = Mb + (j * size);
			for (int k = 0; k < size; ++k, pA++, pB++)
			{
				sumaAuxiliar += (*pA * *pB);
			}
			Mr[i * size + j] = sumaAuxiliar;
		}
	}
}

double **memReserve(int size)
{

	double *val = (double *)malloc(size * size * sizeof(double));

	double **ptr = (double **)malloc(size * size * sizeof(double *));

	for (int i = 0; i < size; ++i)
	{
		ptr[i] = &val[i * size];
	}
	return ptr;
}

void initMatrix_DoublePointers(double **MA, double **MB, double **MC, int size)
{
	int i, j;
	for (i = 0; i < size; ++i)
	{
		for (j = 0; j < size; ++j)
		{
			MA[i][j] = 3.9 * (i - j);
			MB[i][j] = 2.0 * (j + i);
			MC[i][j] = 0.0;
		}
	}
}

void *multMM(void *arg)
{
	int i, j, k;
	int portionSize, initRow, endRow;
	double sum;

	struct arg_struct *args = arg;
	portionSize = args->N / args->Nthreads;
	initRow = (args->idThread) * portionSize;
	endRow = ((args->idThread) + 1) * portionSize;
	for (i = initRow; i < endRow; i++)
	{
		for (j = 0; j < args->N; ++j)
		{
			sum = 0;
			for (k = 0; k < args->N; k++)
			{
				sum += args->Ma[i][k] * args->Mb[k][j];
			}
			args->Mc[i][j] = sum;
		}
	}
	return NULL;
}

void printMatrix_DoublePointers(double **M, int size)
{
	int i, j;
	for (i = 0; i < size; ++i)
	{
		for (j = 0; j < size; ++j)
		{
			printf("	%lf", M[i][j]);
		}
		printf("\n");
	}
	printf("-----------------------------\n");
}
