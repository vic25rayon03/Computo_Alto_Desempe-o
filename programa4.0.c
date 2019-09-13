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

*/
int main(int argc, char *argv[])
{ 
	int *a, *b, i, np, id;
	MPI_Init(&argc,&argv); // Inicializa el ambiente
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	
	if(id==0) // Proceso raíz o 0 
	{
		a=(int *) malloc(np*sizeof(int));
		for(i=0;i<np;i++)
		{
			a[i]=i+1;
		}		
	}
	b=(int *)malloc(sizeof(int));
	MPI_Scatter(a,1,MPI_INT,b,1,MPI_INT,0,MPI_COMM_WORLD);
	printf("dato en proceso %d es = %d \n", id, *b);
	if (id==0) //Mostrar todo el arreglo
	{
		free(a);
		//free(b);
	}		
	free(b);	
	MPI_Finalize(); // Finaliza de ambiente
	return 0;
}
