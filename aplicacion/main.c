#include "c_list.h"
#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

list_t* books;

pthread_mutex_t lock;

typedef struct off_atention{
    int id;
    int seed;
    int loan_succes;
    int loan_fail;
} Off_atention;

Book *create_book(int key);
void *loan(void *);
int LOANS = 1000;
int N_BOOKS = 10000;
int T_Success_L = 0;
int T_Failed_L = 0;
int main(int argc, char const *argv[]){
    struct timeval t_start, t_end;
    int NUMTHREADS = atoi(argv[1]);
    
    books = malloc(sizeof(*books));

    Off_atention * Off_atentions[4];
    List_Init(books);

    for (int i = 0; i < 10000; i++){
         Book * book= create_book(i);
         List_Insert(books, i, book);
    
    }
    pthread_t thrs[NUMTHREADS];
    gettimeofday(&t_start, NULL);
    
    for(int i = 0; i < NUMTHREADS; i++){
        srand(time);
        Off_atention * ofi = malloc(sizeof(Off_atention));
        ofi->id=i;
        ofi->loan_fail=0;
        ofi->loan_succes=0;
        ofi->seed = (int)rand();

        Off_atentions[i] = ofi;
        pthread_create(&thrs[i], NULL, &loan, ofi);
    }
    
    for (int j= 0; j < NUMTHREADS; j++) {
        pthread_join(thrs[j], NULL);
        
        Off_atention * ofi = Off_atentions[j];
        printf("Office %d has finished its workload, successful loans %d, failed loans %d\n", 
        ofi->id, ofi->loan_succes, ofi->loan_fail);

        
        T_Success_L = T_Success_L + ofi->loan_succes;
        
        T_Failed_L = T_Failed_L + ofi->loan_fail;
    }

    gettimeofday(&t_end, NULL);    

    double total_time = (t_end.tv_sec - t_start.tv_sec)*1000 + (t_end.tv_usec - t_start.tv_usec)/1000.0;    
    printf("Simulation done! execution time: %.2f ms\n", total_time);
    printf("Total successful loans %d, total failed loans %d\n", T_Success_L, T_Failed_L);
    printf("Number of remaining available books %d\n", N_BOOKS-T_Success_L);
    return 0;
}


void* loan(void * ofi){
    
    Off_atention *oficce = ofi;
    srand(oficce->seed);
    for(int i = 0; i < LOANS; i++){
        
        int id_book =rand()%N_BOOKS;
        
        node_t * node_book = search_node(books, id_book);
        pthread_mutex_lock(&books->lock);

        if(node_book->book->available==0){        
            
            oficce->loan_succes++;  

        }else{
        
            node_book->book->available = 0;
            oficce->loan_fail++;        
        }
        
        pthread_mutex_unlock(&books->lock);
    }
    return 0;
}



Book *create_book(int key){
    char pre_name[10] = "book_";
    char pos_name[5];    
    sprintf(pos_name, "%d", key);    
    strcat(pre_name, pos_name);
    Book * book = (Book*)malloc(sizeof(Book)); 
    book->name = strdup(pre_name);
    book->id =key;
    book->pages = 69;
    book->year = 2030;
    book->available = 1;
    return book;    
}
