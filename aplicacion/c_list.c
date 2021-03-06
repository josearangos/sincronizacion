#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "c_list.h"


void List_Init(list_t *L) {
	L->head = NULL;
	pthread_mutex_init(&L->lock, NULL);
}

void List_Insert(list_t *L, int value,Book * libro) {
// synchronization not needed
	node_t *new = malloc(sizeof(node_t));
    
	if (new == NULL) {
		perror("malloc");
		return;
	}
	new->key = value;
    new->book = libro;
// just lock critical section
	pthread_mutex_lock(&L->lock);
	new->next = L->head;
	L->head = new;
	pthread_mutex_unlock(&L->lock);
}

int List_Lookup(list_t *L, int key) {
	int rv = -1;
	pthread_mutex_lock(&L->lock);
	node_t *curr = L->head;
    
	while (curr) {
		if (curr->key == key) {
			rv = 0;
			break;
		}
		curr = curr->next;
	}
	pthread_mutex_unlock(&L->lock);
	return rv; // now both success and failure
}


node_t * search_node(list_t *L, int value){
    pthread_mutex_lock(&L->lock);
    node_t *curr = L->head;
    node_t * result = NULL;
    while (curr) {
        if (curr->key == value) {
            result = curr;
            break;
        }
        curr = curr->next;
    }
    pthread_mutex_unlock(&L->lock);
    return result;
}