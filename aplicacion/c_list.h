
#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <stdio.h>
#include <pthread.h>



typedef struct __Book {
    int id;
    char * name;
    int pages;
    int year;
    int available;
} Book;
// basic node structure
typedef struct __node_t {
   int key;
   Book *book;
   struct __node_t *next;
} node_t;

typedef struct __list_t {
    node_t *head;
    pthread_mutex_t lock;
} list_t;

void List_Init(list_t *L);
void List_Insert(list_t *L, int key, Book * book);
int List_Lookup(list_t *L, int key);
node_t * search_node(list_t *L, int key);

#endif