#include<stdio.h>
#include<mpi.h> //No es una biblioteca
main(int argc, char *argv[])
{
//--------------------------------------------------------------------------------------------//
/*		
 ______
|	   |
| P0 s |
|

*/
//--------------------------------------------------------------------------------------------//
	MPI_Status estado;// Almacena informacion de la recepcion 
	MPI_Init(&argc,&argv); //Inicializa el ambiente
	int id,np,dato[5];	
	MPI_Comm_rank(MPI_COMM_WORLD, &id); 
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	if (id==0) //Proceso 0
	{
		for(int i =0;i<5;i++)
		{
			dato[i]=i;
		}
		MPI_Send(dato, 5, MPI_INT,1,10, MPI_COMM_WORLD); 	
		MPI_Recv(dato, 5, MPI_INT,np-1,10, MPI_COMM_WORLD,&estado);
		
		for(int i =0;i<5;i++)
		{
			printf("\n Dato = %d \n", dato[i]); 
		}
	}
	else 
	{
		MPI_Recv(dato, 5, MPI_INT,id-1,10, MPI_COMM_WORLD,&estado);	
		for(int i =0;i<5;i++)
		{
			dato[i]+=1;
		//dato += 1;
			//printf("\n Dato proceso modificado = %d \n", dato[i]); // Datos modificados
		}
		if (id==np-1)
		{
			MPI_Send(dato, 5, MPI_INT,0,10, MPI_COMM_WORLD); 	
		}
		else 
		{
			MPI_Send(dato, 5, MPI_INT,id+1,10, MPI_COMM_WORLD); 
		}
	}
	
	MPI_Finalize(); //Finaliza el ambiente
	return 0;
//---------------------------------------------------------------------------------------------//
}