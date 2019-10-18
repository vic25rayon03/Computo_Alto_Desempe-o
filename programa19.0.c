#include<stdlib.h>
#include<stdio.h>
#include<omp.h> // Se agrega solamente cuando se va a utilizar una función de la librería
#define n 10
//Programa serie
int main ()
{
	int *a, *b, *c,i;
	a=(int *)malloc(n*sizeof(int));
	b=(int *)malloc(n*sizeof(int));	
	c=(int *)malloc(n*sizeof(int));
	//int id, nth;
	//omp_set_num_threads(5);//Es una llamada a una función y debe ser finalizado en punto y coma
	/*	
	#pragma omp parallel num_threads(5) shared(nth) private(id)//Región paralela con cláusula. Debe ir despúes de un constructor
					   // Esto es una cláusula: num_threads(5)
					   // Esto es un constructor: parallel
	{
		id=omp_get_thread_num();//devuelve el identificador del thread
		nth=omp_get_num_threads();//devuelve el numero de hilos generados
		printf("Hola desde el hilo %d de %d \n",id,nth);
		
	}
	*/
	for(i=0;i<n;i++)
	{
		a[i]=i;
		b[i]=i;	
	}
	for(i=0;i<n;i++)
	{
		c[i]=a[i]+b[i];	
	}
	for(i=0;i<n;i++)
	{
		printf("%d",c[i]);	
		
	}
	return 0;
}
