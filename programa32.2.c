#include <stdio.h>
#include <time.h>
#include <omp.h>

long long num_steps = 10000000;
//long long num_steps = 10;
double step;

int main(int argc, char* argv[])
{
	//clock_t start, stop;
	double inicio, fin, tmp;	
	double x, pi, sum=0.0;
	int i;
	inicio=omp_get_wtime();
	step = 1./(double)num_steps;
	
	#pragma omp parallel for private(x,tmp)
	//#pragma omp parallel for private(x)		
	//{
		for (i=0; i<num_steps; i++)
		{
			x = (i + .5)*step;
			tmp= 4.0/(1.0+x*x);
			#pragma omp critical	
			//overhead paralelo		
			//sum = sum + 4.0/(1.+ x*x);
			sum+=tmp;		
		}
	
		pi = sum*step;
		//stop = clock();
		fin=omp_get_wtime();
//----------------------------------------------------------//
	
	//}	
	printf("El  valor de PI es %15.12f\n",pi);
	printf("El tiempo para calcular PI fue %lf milisegundos\n",(fin - inicio));
	return 0;
}

