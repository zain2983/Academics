#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <iostream>
using namespace std;

sem_t a,b; 
int buffer[100];
int i = 0;
int sum=0;
bool flag=true;

// Change this 'x' variable to however many times you want to run the loop 
// Adding 100 numbers takes a lot of time so im only running it 10 times
int x=10;

void* rndm(void* num){
    while(flag){
    	if(i == x){
    		flag=false;
    	}
    	sem_wait(&a);
    	int r=rand()%5+1;
    	buffer[i] = r;
    	cout << "Number "<< buffer[i] << endl;
    	sem_post(&b);
    }
    pthread_exit(nullptr);
}
    
void* func(void* num){
    while(flag){
    	sem_wait(&b);
    	sum = sum + buffer[i];
    	i++;
    	cout << "Sum " << sum << endl ;
    	sem_post(&a);
    }
    pthread_exit(nullptr);
}

int main(){
	pthread_t producer;
	pthread_t consumer;

	sem_init(&a, 0, 1);
	sem_init(&b, 0, 0);

	pthread_create(&producer,nullptr,rndm,nullptr);
	pthread_create(&consumer,nullptr,func,nullptr);

	pthread_join(producer,nullptr);
	pthread_join(consumer,nullptr);
	
	return 0;
}
