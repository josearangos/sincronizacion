#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include "counter.h"

#define THRESHOLD 1024

/* structs */
// code here (if you required it)..

/* start_routine header */
// code here...
void *contador_plus(void *arg);

/* Global variables */
// code here (if you required it)...
int MAXCNT; 
pthread_mutex_t gLock;
int NUMTHREADS;
counter_t contador;



int main(int argc, char *argv[]) { 
     
    pthread_mutex_init(&gLock, NULL);
    
    /* get the command's line parameters */
    // code here...
    MAXCNT = atoi(argv[1]);
    NUMTHREADS = atoi(argv[2]);

    /* Declaration of struct timeval variables */
    // code here...
    struct timeval t_inicial, t_final; // para medir el tiempo 
    double tiempo_total;

    /* Initializing conter */
    // code here...
    init(&contador,THRESHOLD);

    /* Threads handlers */
    // code here...
    pthread_t ths[NUMTHREADS];
    int id_hilos[NUMTHREADS];
    /* Time starts counting */
    // code here...
   gettimeofday(&t_inicial, NULL);

    /* Creating a Threads */
    // code here...
    int i = 0;

    while( i < NUMTHREADS){
        id_hilos[i] = i; // asignamos el id del hilo que se crea al vector
        pthread_create(&ths[i], NULL, contador_plus,(void *)&id_hilos[i]);
        i++;
    }

    /* Threads joins */
    // code here...
    for (int i = 0; i < NUMTHREADS; i++){
        pthread_join(ths[i],NULL);
    }

    /* Time stops counting here */
    // code here...
    printf("VALOR FINAL CONTADOR: %d\n", get(&contador));

    /* get the end time */
    // code here...
    gettimeofday(&t_final, NULL);

    /* get the elapset time (end_time - start_time) */
    // code here...
    tiempo_total = (t_final.tv_sec - t_inicial.tv_sec)*1000  + (t_final.tv_usec - t_inicial.tv_usec)/1000.0;


    /* print the results (number threads employed, counter value, elasep time) */
    // code here...
    printf("NUMTHREADS = %d \n",NUMTHREADS);
    printf("COUNTER VALUE =  %d \n" , get(&contador));
    printf("TOTAL TIME : %f MILISEGUNDOS \n",tiempo_total);


    return 0;
}

/* start_routine definition */
// code here...
void *contador_plus(void* arg){
    //adquirimos el lock global para aumentar el contador 
    int *id_hilo = (int *)arg;
    int current_value = get(&contador);   
    while(current_value < MAXCNT){       
        update(&contador,*id_hilo,1);
        current_value = get(&contador);
    }
    return NULL;
}





