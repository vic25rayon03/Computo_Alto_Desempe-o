#include<stdio.h>
#include<mpi.h> //No es una biblioteca
main(int argc, char *argv[])
{
//--------------------------------------------------------------------------------------------//
	MPI_Init(&argc,&argv); //Inicializa el ambiente
	int rank,np;	
	MPI_Comm_rank(MPI_COMM_WORLD,&rank); // Es un comunicador global (COMUNICADOR,VARAIBLE)	
	MPI_Comm_size(MPI_COMM_WORLD, &np);// Recibe informacion del comunicador y de una variable de cuantos procesos mandamos a llamar
	//printf("\n Hola mundo");
	
	printf("\n Hola desde el proceso %d de %d \n",rank,np);
	
	
	MPI_Finalize(); //Finaliza el ambiente
	return 0;
//---------------------------------------------------------------------------------------------//
}
