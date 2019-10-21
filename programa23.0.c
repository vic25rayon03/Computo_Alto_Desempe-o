#include <stdio.h>
#include <omp.h>
#include<unistd.h>
#define NUM_THREADS 4
#define STATIC_CHUNK 5
#define DYNAMIC_CHUNK 5
#define NUM_LOOPS 20
#define SLEEP_EVERY_N 3

int main( ) 
{
    int nStatic1[NUM_LOOPS],  nStaticN[NUM_LOOPS]; //Configuracion para estático
    int nDynamic1[NUM_LOOPS], nDynamicN[NUM_LOOPS]; //Configuración para dinámico
    int nGuided[NUM_LOOPS];	//Configuración para guiado
    int i;

omp_set_num_threads(NUM_THREADS);

#pragma omp parallel private(i)
    {
//------------------------- Chunk = 1 Estático --------------------------------------//
        #pragma omp for schedule(static, 1) //Chunk 1
        for (i = 0 ; i < NUM_LOOPS ; ++i) 
        {
            if ((i % SLEEP_EVERY_N) == 0) 
                sleep(0);
            nStatic1[i] = omp_get_thread_num( ); //Estático con 1
        }
//-------------------------- Chunk = 5 Estatico---------------------------------------//
	#pragma omp for schedule(static, STATIC_CHUNK) //Chunk 5
        for (i = 0 ; i < NUM_LOOPS ; ++i) 
        {
            if ((i % SLEEP_EVERY_N) == 0) 
                sleep(0);
            nStaticN[i] = omp_get_thread_num( ); //Estático con 5
        }
//-------------------------- Chunk = 1 Dinamico --------------------------------------//
	#pragma omp for schedule(dynamic, 1) //Chunk 1
        for (i = 0 ; i < NUM_LOOPS ; ++i) 
        {
            if ((i % SLEEP_EVERY_N) == 0) 
                sleep(0);
            nDynamic1[i] = omp_get_thread_num( ); //Dinámico con 1
        }

//-------------------------- Chunk = 5 Dinamico --------------------------------------//
	#pragma omp for schedule(dynamic, DYNAMIC_CHUNK) //Chunk 5
        for (i = 0 ; i < NUM_LOOPS ; ++i) 
        {
            if ((i % SLEEP_EVERY_N) == 0) 
                sleep(0);
            nDynamicN[i] = omp_get_thread_num( ); //Dinámico con 5
        }

//-------------------------- Chunk guiado --------------------------------------------//
	#pragma omp for schedule(guided, 4) //Guiado con 4
        for (i = 0 ; i < NUM_LOOPS ; ++i) 
        {
            if ((i % SLEEP_EVERY_N) == 0) 
                sleep(0);
            nGuided[i] = omp_get_thread_num( ); //Guiado con 4
        }
//------------------------------------------------------------------------------------//

        
    }    
        /*AGREGAR PARA LOS OTROS ARREGLOS*/

    printf("------------------------------------------------\n");
    printf("| static | static | dynamic | dynamic | guided |\n");
    printf("|    1   |    %d   |    1    |    %d    |        |\n",
             STATIC_CHUNK, DYNAMIC_CHUNK);
    printf("------------------------------------------------\n");

    for ( i=0; i<NUM_LOOPS; ++i) 
    {
        printf("|    %d   |    %d   |    %d    |    %d    |"
                 "    %d   |\n",
                 nStatic1[i], nStaticN[i],
                 nDynamic1[i], nDynamicN[i], nGuided[i]);
    }

    printf("------------------------------------------------\n");
}
