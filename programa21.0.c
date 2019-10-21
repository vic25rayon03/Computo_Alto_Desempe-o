
#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include<omp.h>
#define n 10

void llenaArreglo(int *a);
void suma(int *a,int *b,int *c);

main()
{

	int max,*a,*b,*c;


	a=(int *)malloc(sizeof(int)*n);
	b=(int *)malloc(sizeof(int)*n);
	c=(int *)malloc(sizeof(int)*n);

	llenaArreglo(a);
	llenaArreglo(b);

	suma(a,b,c);
}

void llenaArreglo(int *a)
{
 	int i;
	for(i=0;i<n;i++)
	{
   		a[i]=rand()%n;
   		printf("%d\t", a[i]);
    	}
   		printf("\n");
}
	
void suma(int *A, int *B, int *C)
{
	int i;
	int id,nth;
	omp_set_num_threads(n);
	#pragma omp parallel shared(nth) private(id) private(i)
	{
		id=omp_get_thread_num();//devuelve el identificador del thread
		nth=omp_get_num_threads();//devuelve el numero de hilos generados
	  
		for(i=id;i<n;i=i+nth)
		{
		        C[i]=A[i]+B[i];
		        //printf("%d\t", C[i]);
			printf("C[%d] = %d del hilo %d\n",i,C[i],id);
   		}
	}
}



