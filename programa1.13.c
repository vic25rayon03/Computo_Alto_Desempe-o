#include<stdio.h>
#include<stdlib.h>
#include<mpi.h> //No es una biblioteca
#include<math.h>
#define p printf
#define NPROCS 8
int main(int argc,char *argv[])
{
	int rank,new_rank,sendbuf,recvbuf,numtasks, ranks1[4]={0,1,2,3},ranks2[4]={4,5,6,7};
	MPI_Group orig_group,new_group;
	MPI_Comm new_comm;
	MPI_Init(&argc,&argv); //Inicializa el ambiente
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
//----------------------------------------------------------------------------------------------//
	sendbuf=rank;
	/*obtener el manejador de grupo original */
	MPI_Comm_group(MPI_COMM_WORLD,&orig_group);
	//Divide las tareas en dos grupos distintos basados en su numero de rank
	if (rank<NPROCS/2)
	{
		MPI_Group_incl(orig_group,NPROCS/2,ranks1,&new_group);	
	}
	else
	{
		MPI_Group_incl(orig_group,NPROCS/2,ranks2,&new_group);
	}
	/* Crea un nuevo comunicador y se realizan comunicaciones colectivas */
	MPI_Comm_create(MPI_COMM_WORLD, new_group,&new_comm);
	MPI_Allreduce(&sendbuf,&recvbuf,1,MPI_INT,MPI_SUM,new_comm);

	MPI_Group_rank(new_group,&new_rank); //Permite obtener el identificador al grupo
	//MPI_Comm_rank(new_comm,&new_rank);//Se utiliza cualquiera de los dos
	p("rank = %d newrank = %d recvbuf = %d\n",rank,new_rank,recvbuf);

//----------------------------------------------------------------------------------------------//
	if(numtasks!=NPROCS)
	{
		p("Se debe especificar MP_PROCS= %d . Terminando.\n", NPROCS);	
	}
	MPI_Finalize(); //Fin del ambiente
	return 1;
}
