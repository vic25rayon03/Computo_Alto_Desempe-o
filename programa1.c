#include<stdio.h>
#include<mpi.h> //No es una biblioteca
main(int argc, char *argv[])
{
	MPI_Init(&argc,&argv); //Inicializa el ambiente
	printf("\n Hola mundo");
	
	
	
	MPI_Finalize(); //Finaliza el ambiente
	return 0;
}
