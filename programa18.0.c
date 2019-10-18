#include<stdlib.h>
#include<stdio.h>
#include<omp.h> // Se agrega solamente cuando se va a utilizar una función de la librería
int main ()
{
	int id, nth;
	//omp_set_num_threads(5);//Es una llamada a una función y debe ser finalizado en punto y coma
	#pragma omp parallel num_threads(5)//Región paralela con cláusula. Debe ir despúes de un constructor
					   // Esto es una cláusula: num_threads(5)
					   // Esto es un constructor: parallel
	{
		id=omp_get_thread_num();//devuelve el identificador del thread
		nth=omp_get_num_threads();//devuelve el numero de hilos generados
		printf("Hola desde el hilo %d de %d \n",id,nth);
		
	}
	
	return 0;
}
