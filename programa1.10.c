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
	MPI_Status estado;// Almacena informacion de la recepcion 
	int *M,i,j,id,np; 
	int n=15, m=10, sobran,nren,aux,var;
	MPI_Init(&argc,&argv); //Inicializa el ambiente
	MPI_Comm_rank(MPI_COMM_WORLD, &id); 
	MPI_Comm_size(MPI_COMM_WORLD, &np);
        //Tareas proceso 0
	if (id==0)
	{	
		nren=n/(np-1);
		sobran=n%(np-1);
		//Formar matriz
		M = (int *) malloc(n*m*sizeof(int));
		for (i=0;i<n*m;i++)
		{
			*(M+i)=i+1; //Llenado de la matriz
		}
		//Imprime matriz
		printf("\n Matriz sin procesar \n");
		for(i=0;i<n;i++)
		{
			for(j=0;j<m;j++)
			{
				printf("%d\t", M[i * m + j]);
			}
		
		}
		
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
			printf("\n aux= %d de para proceso %d \n", aux,i+1);
			}
			MPI_Send(&aux,1,MPI_INT,i+1,i+1,MPI_COMM_WORLD);
			MPI_Send(&M[var*m+0],aux*m,MPI_INT,i+1,i+1,MPI_COMM_WORLD);
			var=var+aux;
			sobran-=1;
			//}
		}


		printf("Esperando recibir\n");
		var=0;
		//Espera recibir		
		for (i=0;i<np-1;i++)
		{
			MPI_Recv(&aux,1,MPI_INT,i+1,i+1,MPI_COMM_WORLD,&estado);
			MPI_Recv(&M[var*m+0],aux*m,MPI_INT,i+1,i+1,MPI_COMM_WORLD,&estado);
			var=var+aux;
		}

		//Impresion matriz procesada
		printf("\nMatriz procesada\n");
		for (i=0;i<n;i++)
		{
			for (j=0;j<m;j++)
			{
				printf("%d \t",M[i*m+j]);
			}
			printf("\n");
			
		}
		free(M);
	}//fin proceso 0

	//Tareas procesos esclavos	
	else
	{
                MPI_Recv(&aux,1,MPI_INT,0,id,MPI_COMM_WORLD,&estado);         
		M = (int *) malloc(aux*m*sizeof(int));
		MPI_Recv(M,aux*m,MPI_INT,0,id,MPI_COMM_WORLD,&estado);
		
		for(i=0;i<aux;i++)
		{
			for(j=0;j<m;j++)
			{
				M[i*m+j]+=2;
			}
		}

		MPI_Send(&aux,1,MPI_INT,0,id,MPI_COMM_WORLD);
		MPI_Send(M,aux*m,MPI_INT,0,id,MPI_COMM_WORLD);
		free(M);
	
	}
	MPI_Finalize(); //Finaliza el ambiente
	return 0;
} 
