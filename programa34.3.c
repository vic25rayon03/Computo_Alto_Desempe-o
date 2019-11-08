#include<stdlib.h>
#include<stdio.h>
#include <omp.h>
#define p printf

int main (int argc, char *argv[])
{
	#pragma omp parallel num_threads(4)
	{
		#pragma omp single
		{
			p("A ");
			#pragma omp task			
			{p("race ");p("(Hilo: %d)",omp_get_thread_num());}
			#pragma omp task			
			{p("car "); p("(Hilo: %d)",omp_get_thread_num());}
			#pragma omp taskwait
			p("Esperamos?");
			//p("(Hilo: %d)",omp_get_thread_num());
			
		}	
	}
	p("\n");
	return 0;
}
