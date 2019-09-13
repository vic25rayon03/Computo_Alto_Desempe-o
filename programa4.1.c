#include<stdio.h>
#include<stdlib.h>
#include<mpi.h> 
/*
-------------------MPI_Scatter()-----------------------
Operacion recíproca a gather

		  /P0 1
		 / P1 2
P0              /  P2 3
 _ _ _ _ _ _ _ /   P3 4
|_|_|_|_|_|_|_|--->P4 5
 Proceso       \   P5 6
   raíz         \  P6 6
                 \ P7 7
                  \

Arreglo de tamaño np*5

*/
#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(int argc, char *argv[])
{
	int *a, *b, i, id, np, arr_size=5;
	MPI_Init(&argc,&argv); // Inicializa el ambiente
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &np);

	if(id==0) //Proceso 0
	{ 
		a=(int *)malloc(np*arr_size*sizeof(int));
		for(i=0;i<np*arr_size;i++)
		{
			a[i]=i;
		}
	}
	b=(int *)malloc(arr_size*sizeof(int));
	MPI_Scatter(a,arr_size,MPI_INT,b,arr_size,MPI_INT,0,MPI_COMM_WORLD);
	printf("Proceso %d Valores = [ ",id);
	for(i=0;i<arr_size;i++)
	{
		printf("%d ",b[i]);
	}
	printf("]\n");

	free(a);
	free(b);
	MPI_Finalize(); // Finaliza de ambiente
	return 0;
}
