#include "prog2_1.h"
#include <pthread.h>
#include <stdio.h>
#include <gmp.h>
#include <unistd.h>
#include <stdlib.h>

mpz_t globalCounter;
TSAFELIST *numberList;
static pthread_mutex_t counterguard = PTHREAD_MUTEX_INITIALIZER;

void getNextNum(mpz_t num){
     pthread_mutex_lock(&counterguard);
     mpz_add_ui(globalCounter, globalCounter, 2);
     mpz_set(num,globalCounter);
     pthread_mutex_unlock(&counterguard);
}

void * generatePrimes(void *args){
     mpz_t tocheck;
     mpz_init(tocheck);
     for(;;){
          getNextNum(tocheck);
          int test = mpz_probab_prime_p(tocheck, 100000);
          if(test > 0){
               tSafeEnqueue(numberList, tocheck);
          }
     }
}

int main(int argc, char *argv[]){
	printf("Assignment #2-2, Joseph Tinglof, jbtinglof@gmail.com\n");
	if(argc < 3){
		fprintf(stderr,"Incorrect number of arguments\n");
		return 1;
     }
     numberList = tSafeConstruct();
     mpz_init(globalCounter);
     int arg1 = atoi(argv[1]);
     int arg2 = atoi(argv[2]);
     mpz_ui_pow_ui(globalCounter, 2, (arg2 - 1));
     mpz_add_ui(globalCounter,globalCounter, 1);
     pthread_t *threads = (pthread_t*)malloc(sizeof(pthread_t)*4);
     for(int i = 0; i < 4; i++){
          pthread_create(threads+i,NULL,generatePrimes,NULL);
     }

     int i = 0;
     while(i < arg1){
          TSAFEDATA answer = tSafeDequeue(numberList);
          if(answer.isValid == 1){
               mpz_out_str(stdout,10,answer.value);
               printf("\n");
               mpz_clear(answer.value);
               i++;
               usleep(1000);
          } else{
               usleep(1000);
          }
     }
     return 0;
}
