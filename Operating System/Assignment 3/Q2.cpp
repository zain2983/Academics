#include <iostream>
#include <pthread.h>
#include <mutex>
#include <semaphore.h>
#include <unistd.h>
using namespace std;

const int BUFFER_SIZE = 1;
const int MAX_ITEMS = 100;

mutex mtx;
sem_t full, mt;  // mt = empty 

int buffer = 0;
int itemsProduced = 0;
int itemsConsumed = 0;

void* producer(void* arg) {
    for (int i = 1; i <= MAX_ITEMS; i++) {
        sem_wait(&mt);
        lock_guard<mutex> lock(mtx);
        buffer = i;
        itemsProduced++;
        cout << "Produced : " << itemsProduced << endl;
        sem_post(&full);
    }
    return NULL;
}

void* consumer(void* arg) {
    while (itemsConsumed < MAX_ITEMS) {
        sem_wait(&full);
        lock_guard<mutex> lock(mtx);
        int item = buffer;
        itemsConsumed++;
        cout << "Consumed : " << item << endl;
        sem_post(&mt);
    }
    return NULL;
}

int main() {    
    sem_init(&full, 0, 0);
    sem_init(&mt, 0, BUFFER_SIZE);

    pthread_t producer_thread, consumer_thread;
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    sem_destroy(&full);
    sem_destroy(&mt);

    return 0;
}
