#include <iostream>
#include <pthread.h>
#include <semaphore.h>
using namespace std;


#define NUM_ITERATIONS 5

int balance = 1000;
sem_t semaphore;

void* subtract(void* arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        sem_wait(&semaphore);
        balance -= 200;
        sem_post(&semaphore);
    }
    //cout << "Updated balance: " << balance << endl;
    return NULL;
}

int main() {
    pthread_t th_a, th_b, th_c;
    sem_init(&semaphore, 0, 1);
    
    cout << "Initial balance: " << balance << endl;

    pthread_create(&th_a, NULL, subtract, NULL);
    pthread_create(&th_b, NULL, subtract, NULL);
    pthread_create(&th_c, NULL, subtract, NULL);

    pthread_join(th_a, NULL);
    pthread_join(th_b, NULL);
    pthread_join(th_c, NULL);
    
    sem_destroy(&semaphore);

    cout << "Final balance: " << balance << endl;

    return 0;
}





