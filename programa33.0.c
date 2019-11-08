#include <stdio.h>
#include <time.h>
#include <omp.h>

void report_num_threads(int nivel)
{
	#pragma omp single
	{
		printf("Nivel %d: Numero de hilos en el equipo - %d \n",nivel, omp_get_num_threads());	
	}
}

int main()
{
	omp_set_nested(1);
	#pragma omp parallel num_threads(2)
	{
		report_num_threads(1);
		#pragma omp parallel num_threads(2)
		{
			report_num_threads(2);
			#pragma omp parallel num_threads(2)
			{
				report_num_threads(3);			
			}		
		}
	}

	return(0);
}
