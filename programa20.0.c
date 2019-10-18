#include<stdlib.h>
#include<stdio.h>
#include<omp.h> // Se agrega solamente cuando se va a utilizar una función de la librería
#define n 10
//Programa paralelo
int main ()
{
	int *a, *b, *c,i,id,ini,fin;
	a=(int *)malloc(n*sizeof(int));
	b=(int *)malloc(n*sizeof(int));	
	c=(int *)malloc(n*sizeof(int));
	//int id, nth;
	//omp_set_num_threads(5);//Es una llamada a una función y debe ser finalizado en punto y coma
	
	for(i=0;i<n;i++)
	{
		a[i]=i;
		b[i]=i;	
	}
		
	//#pragma omp parallel num_threads(5) private(id)//Región paralela con cláusula. Debe ir despúes de un constructor
					   // Esto es una cláusula: num_threads(5)
					   // Esto es un constructor: parallel
	#pragma omp parallel private(id)	
	{
		id=omp_get_thread_num();
		//ini=id*5;
		//fin=(id+1)*5;
		//for(i=ini;i<fin;i++)
		for(i=id*5;i<(id+1)*5;i++)		
		{
			c[i]=a[i]+b[i];				
			
		}		

	}

	
	
	for(i=0;i<n;i++)
	{
		printf("%d\n",c[i]);	
		
	}
	return 0;
}
