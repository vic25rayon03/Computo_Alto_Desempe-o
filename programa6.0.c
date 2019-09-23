#include<stdio.h>
#include<stdlib.h>
#include<mpi.h> 
int main(int argc, char *argv[])
{
	int dato,id,reduction=0;
	MPI_Init(&argc,&argv); // Inicializa el ambiente
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	dato=id+1;
	MPI_Reduce(&dato,&reduction,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	printf("Reduction de proceso %d es %d \n",id,reduction);
	MPI_Finalize(); // Finaliza de ambiente
	return 0;
}
