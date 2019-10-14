#include<stdlib.h>
#include<stdio.h>
#include<omp.h> // Se agrega solamente cuando se va a utilizar una función de la librería
int main ()
{
	omp_set_num_threads(5);//Es una llamada a una función y debe ser finalizado en punto y coma
	#pragma omp parallel //Región paralela
	{
		printf("Hola mundo\n");
	}
	return 0;
}
