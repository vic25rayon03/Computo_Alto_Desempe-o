#include<stdio.h>
#include<stdlib.h>
#include<mpi.h> 

/*	A		    +		B		    =		C
 _______________________	 _______________________	 _______________________ 
|*|*|*|*|*|*|*|*|*|*|*|*|	|*|_|_|_|_|_|_|_|_|_|_|_|	|*|*|*|*|*|*|*|*|*|*|*|*|
|_|_|_|_|_|_|_|_|_|_|_|_|	|*|_|_|_|_|_|_|_|_|_|_|_|	|_|_|_|_|_|_|_|_|_|_|_|_|
|_|_|_|_|_|_|_|_|_|_|_|_|	|*|_|_|_|_|_|_|_|_|_|_|_|	|_|_|_|_|_|_|_|_|_|_|_|_|
|_|_|_|_|_|_|_|_|_|_|_|_|	|*|_|_|_|_|_|_|_|_|_|_|_|	|_|_|_|_|_|_|_|_|_|_|_|_|
|_|_|_|_|_|_|_|_|_|_|_|_|	|*|_|_|_|_|_|_|_|_|_|_|_|	|_|_|_|_|_|_|_|_|_|_|_|_|
|_|_|_|_|_|_|_|_|_|_|_|_|  _|_  |*|_|_|_|_|_|_|_|_|_|_|_|  ___  |_|_|_|_|_|_|_|_|_|_|_|_|
|_|_|_|_|_|_|_|_|_|_|_|_|   |   |*|_|_|_|_|_|_|_|_|_|_|_|  ___  |_|_|_|_|_|_|_|_|_|_|_|_|
|_|_|_|_|_|_|_|_|_|_|_|_|	|*|_|_|_|_|_|_|_|_|_|_|_|	|_|_|_|_|_|_|_|_|_|_|_|_|
|_|_|_|_|_|_|_|_|_|_|_|_|	|*|_|_|_|_|_|_|_|_|_|_|_|	|_|_|_|_|_|_|_|_|_|_|_|_|
|_|_|_|_|_|_|_|_|_|_|_|_|	|*|_|_|_|_|_|_|_|_|_|_|_|	|_|_|_|_|_|_|_|_|_|_|_|_|
|_|_|_|_|_|_|_|_|_|_|_|_|	|*|_|_|_|_|_|_|_|_|_|_|_|	|_|_|_|_|_|_|_|_|_|_|_|_|

Scater(A)
Broadcast(B)
	Todos colocan una parte de C
Gather (C)
*/

int main(int argc, char *argv[])
{
	int *A, *B, *C,*Ap, *Cp, i, id, np, j,k ;
	MPI_Init(&argc,&argv); // Inicializa el ambiente
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &np);

	B=(int *)malloc(10*10*sizeof(int));
	Ap=(int *)malloc(2*10*sizeof(int));
	Cp=(int *)malloc(2*10*sizeof(int));		

	if(id==0) //Proceso 0
	{ 
		A=(int *)malloc(10*10*sizeof(int));
		for(i=0;i<100;i++) //Llenar A
		{
			//for(j=0;j<10;j++) //Llenar A
			//{			
				A[i]=i;
			//}
		}	
		
	}
	
	MPI_Scatter(A,20,MPI_INT,Ap,20,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Bcast(B,100,MPI_INT,0,MPI_COMM_WORLD);
	
	//Producto de matrices
	for(i=0;i<2;i++)
	{
		for(j=0;j<10;j++)
		{
			Cp[i*10+j]=0;		
		}	
	}
	for(int k=0;k<10;k++)
	{
		Cp[i*10+j]+=Ap[i*10+k]*B[k*10+j];
	}
	

	for(i=0;i<2;i++)//Muestra de datos
	{
		for(j=0;j<10;j++)
		{		
			printf("%d ",Ap[i]);
		}
		printf("\n")
	}
	free(Ap);
	free(B);
	free(Cp);			
	MPI_Finalize(); // Finaliza de ambiente
	return 0;
}
