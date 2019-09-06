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
    |_|_|_|_|_|_|_|_|_|_|_|_|_|_|_| _|   nxm
                10x15

Convertir a matriz bidimensional

 _________________________________
|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_| nxm

nren = nrenglones/np --> 10/3

sobran = nrenglones % np


    P1--- 6+1
   /
  /
P0--P2--- 6+1
  \
   \
    P3--- 6


int n=30, m=20, sobran 0;
nren = (n/np)
sobran = nren % 20
for(i=0; i<np-1;i++)
	si sobran > 0
		enviar (nren+1)
		enviar nren+1 renglones
	si no
		enviar nren
		enviar nren renglones
	los esclavos
		reciben nren
		reciben nren renglones
		enviar nren renglones
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
-----------------------------------------------------------------------------------------------
*/ 
//--------------------------------------------------------------------------------------------/
//---------------------------------- Suma de matrices ----------------------------------------//
	MPI_Status estado;// Almacena informacion de la recepcion
	int *M1,*M2,i,j,id,np; //Declaracion de matriz 1 (M1) y matriz 2(M2)
	int n=6, m=3, sobran,nren,aux,var;
	MPI_Init(&argc,&argv); //Inicializa el ambiente
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
         
	// Tareas proceso 0
	if (id==0)
	{
		nren=n/(np-1);
		sobran = n%(np-1);

		//Formar y Llenar Las Matrices
		M1 = (int *) malloc(n*m*sizeof(int));// Formación de la matriz 1
		M2 = (int *) malloc(n*m*sizeof(int));// Formación de la matriz 2
		for (i=0;i<n*m;i++)
		{
			*(M1+i)=i; //Llenado de la matriz 1
			*(M2+i)=i; //Llenado de la matriz 2
		}

		//Imprime la Matriz 1
		printf("\nMatriz 1 sin procesar\n");
		for(i=0; i<n;i++)
		{
			for(j=0;j<m;j++)
			{
				printf("%d\t",M1[i*m+j]);
			}
			printf("\n");
		}

		//Imprime la Matriz 2
		printf("\nMatriz 2 sin procesar\n");
		for(i=0; i<n;i++)
		{
			for(j=0;j<m;j++)
			{
				printf("%d\t",M2[i*m+j]);
			}
			printf("\n");
		}

		printf("\n");
		var=0;
		for (i=0;i<np-1;i++)
		{
			if (sobran>0)
			{
				aux=nren+1;
			}	
			else
			{
				aux=nren;
			}
			printf("%d de %d para proceso %d\n",aux,n,i+1);
			MPI_Send(&aux,1,MPI_INT,i+1,i+1,MPI_COMM_WORLD);
			MPI_Send(&M1[var*m+0],aux*m,MPI_INT,i+1,i+1,MPI_COMM_WORLD); // Envio matriz 1
			MPI_Send(&M2[var*m+0],aux*m,MPI_INT,i+1,i+1,MPI_COMM_WORLD); // Envio matriz 2
			var=var+aux;
			sobran-=1;
		}
	
		printf("\nEsperando Recibir \n");
		var = 0;
		for (i=0;i<np-1;i++)
		{
			MPI_Recv(&aux,1,MPI_INT,i+1,i+1,MPI_COMM_WORLD,&estado);
			MPI_Recv(&M1[var*m+0],aux*m,MPI_INT,i+1,i+1,MPI_COMM_WORLD,&estado); // Recepcion Matriz 1
			MPI_Recv(&M2[var*m+0],aux*m,MPI_INT,i+1,i+1,MPI_COMM_WORLD,&estado); // Recepcion Matriz 2
			var=var+aux;
		}

		printf("\nMatriz Procesada\n");
		for (i=0;i<n;i++)
		{
			for (j=0;j<m;j++)
			{
				printf("%d \t",M1[i*m+j]);
			}
			printf("\n");
		}
		free(M1); // Liberar Matriz 1
		free(M2); // Liberar Matriz 2
		}

		//Tareas Procesos Esclavos
		else
		{
		        MPI_Recv(&aux,1,MPI_INT,0,id,MPI_COMM_WORLD,&estado);        
			M1 = (int *) malloc(aux*m*sizeof(int));
			M2 = (int *) malloc(aux*m*sizeof(int));
			MPI_Recv(M1,aux*m,MPI_INT,0,id,MPI_COMM_WORLD,&estado); // Recepcion Matriz 1
			MPI_Recv(M2,aux*m,MPI_INT,0,id,MPI_COMM_WORLD,&estado); // Recepcion Matriz 2
	
			for(i=0;i<aux;i++)
			{
				for(j=0;j<m;j++)
				{
					M1[i*m+j]+=M2[i*m+j];
				}
			}
			MPI_Send(&aux,1,MPI_INT,0,id,MPI_COMM_WORLD);
			MPI_Send(M1,aux*m,MPI_INT,0,id,MPI_COMM_WORLD); // Envio Matriz 1
			MPI_Send(M2,aux*m,MPI_INT,0,id,MPI_COMM_WORLD); // Envio Matriz 2
			free(M1); // Liberar Matriz 1
			free(M2); // Liberar Matriz 2
		}
		MPI_Finalize(); //Finaliza el ambiente
		return 0;
} 
