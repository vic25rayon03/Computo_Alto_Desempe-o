#include<stdio.h>
#include<stdlib.h>
#include<mpi.h> 

void main(int argc, char *argv[])
{
    int i,id,np,nrec,varinicio,varfin,n=1000;
    double h, pip, x,pi;
    MPI_Init(&argc,&argv); // Inicializa el ambiente
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD,&np);    
    nrec=n/np;
    varinicio=id*nrec;
    varfin=(id+1)*nrec-1;    
    h=1.0/(double) n;
    pi=0.0;
    for(i=varinicio;i<varfin;i++)
    {
        x=(double)i/(double) n;
        pip += (1.0/(1.0+x*x))*h;
    }
    MPI_Reduce(&pip,&pi,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
    if(id==0)
    {
        printf("El resultado es: %22.16e\n", 4.0*pi);
    }
    MPI_Finalize(); // Finaliza de ambiente
    return 0;
}

