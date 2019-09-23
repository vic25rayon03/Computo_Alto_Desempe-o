#include<stdio.h>
#include<stdlib.h>
#include<mpi.h> 

void main(int argc, char *argv[])
{
	int i,n=1000;
	double h, pi, x;
//	MPI_Init(&argc,&argv); // Inicializa el ambiente
//	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	h=1.0/(double) n;
	pi=0.0;
	for(i=0;i<n;i++)
	{
		x=(double)i/(double) n;
		pi += (1.0/(1.0+x*x))*h;
	}
	printf("Pi es aproximadamente %22.16e\n", 4.0*pi);

//	MPI_Finalize(); // Finaliza de ambiente
	return 0;
}
