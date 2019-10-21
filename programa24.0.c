#include <stdio.h>
#include <omp.h>
#include<unistd.h>
#include<stdlib.h>
#include<math.h>
main()
{
	int i;

	#pragma omp parallel num_threads(5) //Región paralela
	{
		#pragma omp critical //Región crítica
		{
			i++;
		}	
	}
	printf("El valor de i es: %d\n",i);
	return 0;
}
