#include<stdio.h>
#include<stdlib.h>
#include<mpi.h> 

int main(int argc, char *argv[])
{
	//int *dato,id,reduction;
	int id;
	char dato[4],reduction[4];	
	MPI_Init(&argc,&argv); // Inicializa el ambiente
	MPI_Comm_rank(MPI_COMM_WORLD, &id);

	//dato=id+1;
	for(int i=0;i<4;i++) //Llenado del arreglo
	{
		//dato[i]='a'+4*id+i;
		dato[i]=1;
	} 
	//MPI_Allreduce(&dato,&reduction,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
	MPI_Reduce(dato,reduction,4,MPI_CHAR,MPI_SUM,0,MPI_COMM_WORLD);
	if(id==0)
	{
		//printf("%d",reduction[0]);
		for(int i=0;i<4;i++)		
		{
			printf("%d",reduction[i]);
		}
	}
	MPI_Finalize(); // Finaliza de ambiente
	return 0;
}
