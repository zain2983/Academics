#include <iostream>
#include <pthread.h>
#include <mutex>
using namespace std;

int globalCounter = 0;
pthread_mutex_t counterMutex = PTHREAD_MUTEX_INITIALIZER;

void* incrementCounter(void* arg) {
    for (int i = 0; i < 100; ++i) {
        pthread_mutex_lock(&counterMutex);
        globalCounter++;
        pthread_mutex_unlock(&counterMutex);
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, incrementCounter, NULL);
    pthread_create(&thread2, NULL, incrementCounter, NULL);
    //pthread_create(&thread1, NULL, incrementCounter, NULL);
    //pthread_create(&thread2, NULL, incrementCounter, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&counterMutex);

    cout << "Global Counter : " << globalCounter << endl;

    return 0;
}


