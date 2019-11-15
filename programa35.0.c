#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<omp.h>
#define n 5

/*
Sea An*n, Bn, Cn, Dn, y X
Realizar un programa que resuelva las siguientes operaciones
C=AxB
D=AxC
X=C·D

     A		B     C
  _ _ _ _ _	_     _
 |_|_|_|_|_|   |_|   |_|
 |_|_|_|_|_|   |_|   |_|
 |_|_|_|_|_| X |_| = |_|
 |_|_|_|_|_|   |_|   |_|
 |_|_|_|_|_|   |_|   |_|

*/

int main()
{
	int A[n][n],B[n],C[n],D[n],X,i,k;

	#pragma omp parallel num_threads(3) private(k) //Inicio de región paralela
	{
		#pragma omp for
		for(i=0;i<n;i++)
		{
			for(k=0;k<n;k++)
			{
				A[i][k]=(i*n)+k;
			}
			B[i]=i;
		}
//------------------------------------------------------------------------------//
		#pragma omp barrier //Finaliza el Llenado de A y B
		#pragma omp single
		printf("C=\n");
		#pragma omp for
		for(i=0;i<n;i++)
		{
			for(k=0;k<n;k++)
			{
				C[i]+= A[i][k]*B[k];
			}
			printf("%d\n",C[i]);
		}
//------------------------------------------------------------------------------//
		#pragma omp barrier //Finaliza el Calculo de C
		#pragma omp single
		printf("\nD=\n");
		#pragma omp for
		for(i=0;i<n;i++)
		{
			for(k=0;k<n;k++)
			{
				D[i]+= A[i][k]*C[k];
			}
			printf("%d\n",D[i]);
		}

		#pragma omp barrier //Finaliza el Calculo de D
//------------------------------------------------------------------------------//
		#pragma omp for
		for(i=0;i<n;i++)
		{
			X+= C[i]*D[i];
		}
		#pragma omp single
		printf("\nX = %d\n",X);
//------------------------------------------------------------------------------//
		#pragma omp barrier //Finaliza el Calculo de D

	}
	printf("\n");
	return 0;
}
