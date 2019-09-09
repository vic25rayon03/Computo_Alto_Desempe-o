#include<stdio.h>
#include<stdlib.h>
#include<mpi.h> 
int main(int argc, char *argv[])
{ 
	int dato, id,np;
	MPI_Init(&argc,&argv); // Inicializa el ambiente
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	if(id==0) // Proceso 0 
	{
		dato=5;	
	}
	MPI_Bcast(&dato,1,MPI_INT,0,MPI_COMM_WORLD);
	printf("Dato = %d del proceso %d",dato, id);
	MPI_Finalize(); // Finaliza de ambiente
	return 0;
}
