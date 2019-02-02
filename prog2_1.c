#include "prog2_1.h"
#include <pthread.h>
#include <stdlib.h>
#include <gmp.h>

TSAFELIST* tSafeConstruct(){
     TSAFELIST *arr = (TSAFELIST*) malloc(sizeof(TSAFELIST));
     pthread_mutex_init(&(arr->mutex),NULL);
     arr->head = NULL;
     return arr;
}

void tSafeDestruct(TSAFELIST* arr){
     free(&(arr->mutex));
     free(arr);
}

void tSafeEnqueue(TSAFELIST *arr, mpz_t newNum){
     pthread_mutex_lock(&(arr->mutex));
     TSAFENODE *newNode = (TSAFENODE*) malloc(sizeof(TSAFENODE));
     mpz_init(newNode->number);
     mpz_set(newNode->number, newNum);
     newNode->next = NULL;
     if(arr->head == NULL){
          arr->head = newNode;
     } else {
          TSAFENODE *currentNode;
          currentNode = arr->head;
          while(currentNode->next != NULL){
               currentNode = currentNode->next;
          }
          currentNode->next = newNode;
     }
     pthread_mutex_unlock(&(arr->mutex));
}

TSAFEDATA tSafeDequeue(TSAFELIST *arr){
     pthread_mutex_lock(&(arr->mutex));
     TSAFEDATA firstData;
     if(arr->head == NULL){
          firstData.isValid = 0;
          pthread_mutex_unlock(&(arr->mutex));
          return firstData;
     }
     mpz_init(firstData.value);
     mpz_set(firstData.value, arr->head->number);
     firstData.isValid = 1;
     TSAFENODE *temp = arr->head;
     arr->head = arr->head->next;
     free(temp);
     pthread_mutex_unlock(&(arr->mutex));
     return firstData;
}
