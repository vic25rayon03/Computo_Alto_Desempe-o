#include<stdlib.h>
#include<stdio.h>
#include<omp.h> // Se agrega solamente cuando se va a utilizar una función de la librería
int main ()
{
	
	//omp_set_num_threads(5);//Es una llamada a una función y debe ser finalizado en punto y coma
	#pragma omp parallel num_threads(3)//Región paralela con cláusula. Debe ir despúes de un constructor
					   // Esto es una cláusula: num_threads(3)
					   // Esto es un constructor: parallel
	{
		int i=5;
		printf("Hola mundo\n");
		printf("%d\n", i);
		i=i+1;
	}
	printf("%d\n", i);
	return 0;
}
