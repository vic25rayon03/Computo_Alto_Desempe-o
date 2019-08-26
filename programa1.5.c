#include<stdio.h>
#include<mpi.h> //No es una biblioteca
main(int argc, char *argv[])
{
//--------------------------------------------------------------------------------------------//
/*
				dato-->dato
				P0---->P1
*/
//--------------------------------------------------------------------------------------------//
	MPI_Status estado;// Almacena informacion de la recepcion 
	MPI_Init(&argc,&argv); //Inicializa el ambiente
	int id,np,dato;	
	MPI_Comm_rank(MPI_COMM_WORLD, &id); 
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	if (id==0) //Proceso 0
	{
		dato=1;
		//printf("\n Dato antes = %d", dato);
		MPI_Send(&dato, 1, MPI_INT,1,10, MPI_COMM_WORLD); 	
		MPI_Recv(&dato, 1, MPI_INT,np-1,10, MPI_COMM_WORLD,&estado);
		printf("\n Dato proceso 0 = %d \n", dato); 
	}
	else 
	{
		MPI_Recv(&dato, 1, MPI_INT,id-1,10, MPI_COMM_WORLD,&estado);	
		dato += 1;
		printf("\n Dato proceso modificado = %d \n", dato); // Datos modificados
		if (id==np-1)
		{
			MPI_Send(&dato, 1, MPI_INT,0,10, MPI_COMM_WORLD); 	
		}
		else 
		{
			MPI_Send(&dato, 1, MPI_INT,id+1,10, MPI_COMM_WORLD); 
		}
	}
	
	MPI_Finalize(); //Finaliza el ambiente
	return 0;
//---------------------------------------------------------------------------------------------//
}