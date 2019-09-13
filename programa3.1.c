#include<stdio.h>
#include<stdlib.h>
#include<mpi.h> 
int main(int argc, char *argv[])
{ 
	int *a, *b, i, np, id;
	MPI_Init(&argc,&argv); // Inicializa el ambiente
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	a=(int *) malloc(5*sizeof(int));
	for(i=0;i<5;i++)
	{
		a[i]=id*5+i;
	}

	if(id==0) // Proceso raíz o 0 
	{
		b=(int *)malloc(np*5*sizeof(int));	
	}
	MPI_Gather(a,5,MPI_INT,b,5,MPI_INT,0,MPI_COMM_WORLD);
	
	if (id==0) //Mostrar todo el arreglo
	{
		printf("Arreglo del proceso 0 \n");
		for(int i =0;i<np*5;i++)
		{
			printf("%d ",b[i]);
		}
		free(b);
	}		
	free(a);	
	MPI_Finalize(); // Finaliza de ambiente
	return 0;
}
