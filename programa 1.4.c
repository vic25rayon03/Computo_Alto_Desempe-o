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
	MPI_Status estado;	
	MPI_Init(&argc,&argv); //Inicializa el ambiente
	int rank,np,dato=0;	
	MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Es un comunicador global (COMUNICADOR,VARAIBLE)	
	MPI_Comm_size(MPI_COMM_WORLD, &np);// Recibe informacion del comunicador y de una variable de cuantos procesos mandamos a llamar
	//printf("\n Hola mundo");
	if (rank==0) //Proceso 0
	{
		dato=4;
		printf("\n Dato antes = %d", dato);
		MPI_Send(&dato, 1, MPI_INT,1,23, MPI_COMM_WORLD); //Enviar dato (-Búfer de envío- direccion de las variables,cuantos datos se envían, tipo de dato, a quien le voy a mandar la informacion, etiqueta de mensaje(cualquie numero), comunicador)	
		MPI_Recv(&dato, 1, MPI_INT,1,3, MPI_COMM_WORLD,&estado);
		printf("\n Dato = %d", dato); 
	}
	
	if (rank==1) //Proceso 1
	{
		//printf("\n Dato antes =%d", dato); //Antes de la recepción
		MPI_Recv(&dato, 1, MPI_INT,0,23, MPI_COMM_WORLD,&estado);//Enviar dato (-Búfer de envío- direccion de las variables,cuantos datos se envían, tipo de dato, de quien voy a recibir la informacion, etiqueta de mensaje(cualquie numero), comunicador, estado es una variable que se utiliza se guardará informacion del estado de recepción)	
		dato=dato+8;
		MPI_Send(&dato, 1, MPI_INT,0,3, MPI_COMM_WORLD); //Enviar dato (-Búfer de envío- direccion de las variables,cuantos datos se envían, tipo de dato, a quien le voy a mandar la informacion, etiqueta de mensaje(cualquie numero), comunicador)	
		//printf("\n Dato despues=%d", dato); //Despues de la recepcion
	}
	//printf("\n Hola desde el proceso %d de %d \n",rank,np);
	
	MPI_Finalize(); //Finaliza el ambiente
	return 0;
//---------------------------------------------------------------------------------------------//
}