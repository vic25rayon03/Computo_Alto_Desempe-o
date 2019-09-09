#include<stdio.h>
#include<stdlib.h>
#include<mpi.h> 
int main(int argc, char *argv[])
{ 
	int dato, *datos, id,np;
	MPI_Init(&argc,&argv); // Inicializa el ambiente
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &np);

	if(id==0) // Proceso 0 
	{
		datos=(int *)malloc(np*sizeof(int));	
	}
	dato=id+1;
	MPI_Gather(&dato,1,MPI_INT,datos,1,MPI_INT,0,MPI_COMM_WORLD);
	if (id==0)
	{
		for(int i =0;i<np;i++)
		{
			printf("%d \n",datos[i]);
		}
	}
	free(datos);		
	MPI_Finalize(); // Finaliza de ambiente
	return 0;
}
