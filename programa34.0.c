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
			{p("race ");}
			#pragma omp task			
			{p("car");}			
		}	
	}
	p("\n");
	return 0;
}
