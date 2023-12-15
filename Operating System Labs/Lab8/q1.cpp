#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

sem_t semaphore_a;
sem_t semaphore_b;
sem_t semaphore_c;
int count=0;
int x=3;
int y=0;
int z=0;

void *threadFunction1(void *arg) {
	while(1){
		count=0;
		while(count!=3){	
			sem_wait(&semaphore_a);
			printf("a");
			count=count+1;
			}
		sem_post(&semaphore_c);
    }
  	pthread_exit(NULL);
} 

void *threadFunction2(void *arg) {
	while(1){
		sem_wait(&semaphore_b);
		printf("b");
		sem_post(&semaphore_a);
		sem_post(&semaphore_a);
		sem_post(&semaphore_a);
	}
	pthread_exit(NULL);
}


void *threadFunction3(void *arg) {
	while(1){
		sem_wait(&semaphore_c);
		printf("c");
		sem_post(&semaphore_b);  
	}
	pthread_exit(NULL);
}



int main() {
	pthread_t t1;
	pthread_t t2;
	pthread_t t3;
	
    sem_init(&semaphore_a, 0, x);
    sem_init(&semaphore_b, 0, y);
    sem_init(&semaphore_c, 0, z);
    
    pthread_create(&t1, NULL, threadFunction1, NULL);
    pthread_create(&t2, NULL, threadFunction2, NULL);
    pthread_create(&t3, NULL, threadFunction3, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
   
    return 0;
}

