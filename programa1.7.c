#include<stdio.h>
#include<stdlib.h>
#include<mpi.h> //No es una biblioteca
main(int argc, char *argv[])
{
//--------------------------------------------------------------------------------------------//
/*-------------------------------------------------------------------------------------		
		   M
     ______________________________ _
P0  |_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|  |P1
    |_|_|_|_|_|_|_|_|_|_|_|_|_|_|_| _|
    |_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|  |P2
    |_|_|_|_|_|_|_|_|_|_|_|_|_|_|_| _|
    |_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|  |P3
    |_|_|_|_|_|_|_|_|_|_|_|_|_|_|_| _|
    |_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|  |P4
    |_|_|_|_|_|_|_|_|_|_|_|_|_|_|_| _|
    |_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|  |P5
    |_|_|_|_|_|_|_|_|_|_|_|_|_|_|_| _|
                10x15

Convertir a matriz bidimensional

 _________________________________
|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|

------------------------------------------------------------------------------------------------
	Algoritmo

Si P0
 Llenar matriz 
  Para i=0 hasta 5
   Envia parte de matriz M a proceso i+1
  Fin para 
  Para i=o hasta 5
   Recibir en M de proceso i+1
  Fin para
  En otro caso
   Recibir en M
   Modificar M
   Enviari M modificando a P0
  Fin SI
-----------------------------------------------------------------------------------------------*/
//--------------------------------------------------------------------------------------------//
	MPI_Status estado;// Almacena informacion de la recepcion 
	//int id,np,dato[5];
	int *M,i,j,id,np; // *M matriz en tiempo de ejecución
	MPI_Init(&argc,&argv); //Inicializa el ambiente
	MPI_Comm_rank(MPI_COMM_WORLD, &id); 
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	if (np!=6) //Proceso diferente de 6
	{
		printf("\n Deben ser 6 procesos");
		MPI_Finalize();
 		return 0;
	}

	if (id==0)
	{
		M = (int *) malloc(150*sizeof(int));
		for (i=0;i<150;i++)
		{
			*(M+i)=i+1;
		}
		
		for (i=0;i<5;i++)
		{
			MPI_Send(M+30*i,30,MPI_INT,i+1,i+1,MPI_COMM_WORLD);//Proceso 1
		}
		for (i=0;i<5;i++)
		{
			MPI_Recv(M+30*i,30,MPI_INT,i+1,i+1,MPI_COMM_WORLD,&estado);//Proceso 1
		}
		for (i=0;i<10;i++)
		{
			for (j=0;j<15;j++)
			{
				printf("%d \t",M[i*15+j]);
			}
			printf("\n");
			
		}
		free(M);
	}
	else
	{
		M = (int *) malloc(30*sizeof(int));
		MPI_Recv(M,30,MPI_INT,0,id,MPI_COMM_WORLD,&estado);
		for(i=0;i<2;i++)
		{
			for(j=0;j<15;j++)
			{
				M[i*15+j]+=2;
			}
		}
		MPI_Send(M,30,MPI_INT,0,id,MPI_COMM_WORLD);
		free(M);
	
	}
	MPI_Finalize(); //Finaliza el ambiente
	return 0;
//---------------------------------------------------------------------------------------------//
}
