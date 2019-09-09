#include<stdio.h>
#include<stdlib.h>
#include<mpi.h> 
int main(int argc, char *argv[])
{ 
	int id,np;
	char dato[5];
	MPI_Init(&argc,&argv); // Inicializa el ambiente
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	if(id==0) // Proceso 0 
	{
		dato[0]='H';
		dato[1]='O';
		dato[2]='L';
		dato[3]='A';
		dato[4]='!';	
	}
	MPI_Bcast(dato,5,MPI_CHAR,0,MPI_COMM_WORLD);
	printf("\n Dato = %s del proceso %d \n ",dato, id);
	
MPI_Finalize(); // Finaliza de ambiente
	return 0;
}
