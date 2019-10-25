#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<unistd.h>
#include<omp.h>

#define n 1000

/*
	max					
         |
	 _ _ _ _ _ _
	|_|_|_|_|_|_|
	  |   |   |	
	 _|  _|  _|
	|_| |_| |_|
	 |   |   |
	   máximo
	
	
*/

void llenaArreglo(int *a);
int buscaMaximo(int *a);

main()
{

	int max,*arreglo;
	

	arreglo=(int *)malloc(sizeof(int)*n);

	llenaArreglo(arreglo);
	max=buscaMaximo(arreglo);

	printf("El maximo es:%d",max);

}

void llenaArreglo(int *a)
{
	int i;
 	for(i=0;i<n;i++)
   	{
    		a[i]=rand();
   		//printf("%d\n", a[i]);
    	}
}

int buscaMaximo(int *a)
{
	int max[10],i,id,maxi,nth;
  	//max=a[0];
	
	#pragma omp parallel private(max,id) //Region paralela
	{
		id=omp_get_thread_num();
		nth=omp_get_num_threads();
		#pragma omp for
   		 for(i=1;i<n;i++)
		 {
    		 	 if(a[i]>max[i])
		
      			   max[id]=a[i];
			 
   		 }
		if(id==0)//Hilo cero
		{
			maxi=max[0];
			for(i=1;i<n;i++)
			{
				if(max[i]>maxi)
					maxi=max[i];
			}
	}
  }
   	return maxi;
}

