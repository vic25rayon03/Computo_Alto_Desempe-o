#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
main(int argc, char *argv[])
{

	MPI_Status estado;// Almacena informacion de la recepcion 
	int *M,i,j,id,np; 
	int n=15, m=10, sobran,nren,aux,var;
	MPI_Init(&argc,&argv); //Inicializa el ambiente
	MPI_Comm_rank(MPI_COMM_WORLD, &id); 
	MPI_Comm_size(MPI_COMM_WORLD, &np);
          

	if (id==0)
	{	
		M = (int *) malloc(n*m*sizeof(int));// Formación de la matriz
		for (i=0;i<n*m;i++)
		{
			*(M+i)=i+1; //Llenado de la matriz
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
			
			
			MPI_Send(&aux,1,MPI_INT,i+1,i+1,MPI_COMM_WORLD);
			MPI_Send(&M[var*m+0],aux*m,MPI_INT,i+1,i+1,MPI_COMM_WORLD);
			var=var+aux;
			sobran=1;
			}
		
		}
		for (i=0;i<np-1;i++)
		{
			MPI_Recv(&aux,1,MPI_INT,i+1,i+1,MPI_COMM_WORLD,&estado);
			MPI_Recv(&M[var*m+0],aux*m,MPI_INT,i+1,i+1,MPI_COMM_WORLD,&estado);
		}

		for (i=0;i<n;i++)
		{
			for (j=0;j<m;j++)
			{
				printf("%d \t",M[i*m+j]);
			}
			printf("\n");
			
		}
		//free(M);
	}
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
		//free(M);
	
	}
	MPI_Finalize(); //Finaliza el ambiente
	return 0;
} 
