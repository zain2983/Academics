#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <semaphore.h>

using namespace std;

mutex cout_mutex;
sem_t sem;

int next_thread_to_print = 1;

void fact(int x) {
    int factorial = 1;
    for (int i = 1; i <= x; ++i) {
        factorial *= i;
    }

    while (x != next_thread_to_print) {
        this_thread::yield();
    }

    sem_wait(&sem);
    {
        lock_guard<mutex> lock(cout_mutex);
        cout << "Thread " << x << ": " << factorial << endl;
    }

    ++next_thread_to_print;
    sem_post(&sem);
}

int main() {
    sem_init(&sem, 0, 1);
    
    vector<thread> threads;
    for (int i = 1; i <= 10; ++i) {
        threads.emplace_back(fact, i);
    }


    for (thread& thread : threads) {
        thread.join();
    }

    sem_destroy(&sem);

    return 0;
}
