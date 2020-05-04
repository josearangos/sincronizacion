#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/time.h>
#include "counter.h"
#include <syscall.h>


/* structs */
// code here (if you required it)...
typedef struct __myarg_t {
    int a;
    counter_t * b;
    pthread_t  c;
    int d;

} myarg_t;

typedef struct __myret_t {
    int x;
    int y;
} myret_t;
/* start_routine header */
// code here...

counter_t conter;

void *mythread(void *arg);

int 
pthread_join(   pthread_t thread, 
                void ** value_ptr);

int
pthread_create(     pthread_t* thread,
                    const pthread_attr_t* attr,
                    void* (*start_routine)(void*),
                    void* arg);

/* Global variables */
// code here (if you required it)...

int main(int argc, char *argv[]) { 

    /* get the command's line parameters */
    // code here...
    char * APROXIMATION_FACTOR=argv[1];
    char * MAXCNT=argv[2];
    char * NUMTHREADS = argv[3];

    /* Declaration of struct timeval variables */
    // code here...
        struct timeval t,t2;
        int microsegundos;

    /* Initializing conter */
    // code here.
    int FACTOR=atoi(APROXIMATION_FACTOR);
    init(&conter,1);

    /* Threads handlers */
    // code here...

    myret_t *m;
    int rc;
    myarg_t args;
    args.a = atoi(MAXCNT);
    args.b = &conter;
    args.d=FACTOR;
    
    /* Thread creation */
    // code here...

    /* Time starts counting */
    // code here...

    gettimeofday(&t,NULL);

    /* Creating a Threads */
    // code here...
    int count=1;
    while(count<=atoi(NUMTHREADS)){
        pthread_t p;
        args.c = p;
        rc = pthread_create(&p, NULL, mythread, &args);
        
        count+=1;
        // /* Threads joins */
        // // code here...
        pthread_join (p, NULL); 
    }
    
    printf("ya sali\n");

    // /* Time stops counting here */
    // // code here...
        

    // /* get the end time */
    // // code here...
     gettimeofday(&t2,NULL);

    // /* get the elapset time (end_time - start_time) */
    // // code here...
     microsegundos = ((t2.tv_usec - t.tv_usec) + ((t2.tv_sec -t.tv_sec)*1000000.0f));

    // /* print the results (number threads employed, counter value, elasep time) */
    // // code here...
     printf("%i microsegundos \n",microsegundos);

    return 0;
}

/* start_routine definition */
// code here...

void *mythread(void *arg) {
    myarg_t *m = (myarg_t *) arg;
    counter_t * vcount=m->b;
    int vmax=m->a;
    int id=m->c;
    while(get(vcount)<= vmax){
        int vcontador=get(vcount);
        int vmaximo=m->a;
        printf("%d\n",vcontador);
        update(vcount,m->c,m->d);

    }

   // myret_t *r = malloc(sizeof(myret_t));
    int value=get(vcount);

    return NULL;
}