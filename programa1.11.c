#include<stdio.h>
#include<stdlib.h>
#include<mpi.h> //No es una biblioteca
#include<math.h>

#define N 10
#define count 4
#define longBloque 4
#define p printf

int main(int argc, char *argv[])
{
	int A[N][N];
	int id, i, j;
	MPI_Status estado;
	MPI_Init(&argc,&argv); //Inicializa el ambiente
	MPI_Datatype nuevo_tipo;	
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	//MPI_Comm_size(MPI_COMM_WORLD, &np);
	
	MPI_Type_vector(count,longBloque,N,MPI_INT,&nuevo_tipo);
	MPI_Type_commit(&nuevo_tipo);       
	
	if(id==0)
	{
		for(i=0;i<N;i++)
		{
			for(j=0;j<N;j++)
			{
				A[i][j]=i;
				p("%d \t",A[i][j]);
			}		
		p("\n");		
		}
		MPI_Send(&A[0][2],1,nuevo_tipo,1,0,MPI_COMM_WORLD);
	}
	else
	
		if(id==1)
		{
			MPI_Recv(&A[0][0],1,nuevo_tipo,0,0,MPI_COMM_WORLD,&estado);
			for(i=0;i<count;i++)
			{
				for(j=0;j<count;j++)
				{
					p("%d ",A[i][j]);
				}
				p("\n");
			}	
		}	
	
	MPI_Type_free(&nuevo_tipo);
	MPI_Finalize(); //Finaliza el ambiente
	return 0;
} 
