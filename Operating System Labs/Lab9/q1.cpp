#include<iostream>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
using namespace std;

sem_t sem1;
sem_t sem2;
int x=0;

void* increment(void* arg){
	sem_wait(&sem1);
	cout<<"X : "<<x<<endl;
	x++;
	sem_post(&sem1);
	return 0;
}

void* last(void* arg){
	int number= *(int*)arg;
	if((number-1)==(x-1)){
		sem_post(&sem2);
	}
	sem_wait(&sem2);
	cout<<"All threads have finished their execution"<<endl;
	return 0;
}


int main(){
	int n=0;
	cout << "Enter the number of threads : ";
	cin >> n ;
	pthread_t threadIDs[n+1];
	sem_init(&sem1, 0, 1);
	sem_init(&sem2, 0, 0);

	for(int i=0;i<n;i++){
		pthread_create(&threadIDs[i],NULL,increment,&x);
	}
	
	pthread_create(&threadIDs[n+1],NULL,last,&n);
	
	for (int i = 0; i < n+1; i++) {
        	pthread_join(threadIDs[i], NULL);
        }
    
        sem_destroy(&sem1);
        sem_destroy(&sem2);


    
	return 0;
}
