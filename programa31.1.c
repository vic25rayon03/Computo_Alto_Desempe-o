#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<math.h>
/*
#pragma omp section
{
	sentencias
}
Se generan tiempos de espera al crear hilos, y se recomienda tener una sola region paralela
*/

main()
{
	int m[12][10],i,j,id;
	
	#pragma omp parallel private(id,i)
	{
		id=omp_get_thread_num();
		//#pragma omp for
			for(j=0;j<10;i++)
			{
				#pragma omp for
				for(i=0;i<12;i++)
				{
					m[i][j]=id;
					printf("%d",m[i][j]);				
				}
			printf("\n");			
			}	
	}

	return 0;
}

