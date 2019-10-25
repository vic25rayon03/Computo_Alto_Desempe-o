#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

#define n 100

void llenaArreglo(double *a);

double prodpunto(double *a,double *b);

main(){
double res,*a,*b ;

a=(double *)malloc(n*sizeof(double));
b=(double *)malloc(n*sizeof(double));

llenaArreglo(a);
llenaArreglo(b);


res=prodpunto(a,b);
printf("El resultado es %lf",res);


}


void llenaArreglo(double *a){
  int i;
    for(i=0;i<n;i++){
    a[i]=1;

    }


}


double prodpunto(double *a,double *b)
{
  double res=0,resT=0;
  int i;
  #pragma omp parallel private (res)
  {
	res=0;
  	#pragma omp for
	for(i=0;i<n;i++)
	{
		res+=a[i]*b[i];
	}
	#pragma omp critical
	{
		resT+=res;	
	}
  }

  return resT;
}
 
