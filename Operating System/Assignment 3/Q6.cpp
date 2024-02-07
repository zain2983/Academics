#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>
#include <semaphore.h>
#include <unistd.h>       
using namespace std;

const int NUM_PHILOSOPHERS = 5;

mutex print_mutex;
vector<sem_t> forks(NUM_PHILOSOPHERS);

void print(const string &message, int p_id) {
    lock_guard<mutex> lock(print_mutex);
    cout << "Philosopher " << p_id << ": " << message << endl;
}

void philosopher(int p_id) {
    int left_fork = p_id;
    int right_fork = (p_id + 1) % NUM_PHILOSOPHERS;

    while (true) {
        print("is thinking.", p_id);
        this_thread::sleep_for(chrono::seconds(1));

        print("is hungry and waiting for forks.", p_id);

        sem_wait(&forks[left_fork]);
        sem_wait(&forks[right_fork]);

        print("is eating.", p_id);
        this_thread::sleep_for(chrono::seconds(1));

        sem_post(&forks[left_fork]);
        sem_post(&forks[right_fork]);
        print("has finished eating and released the forks.", p_id);
    }
}

int main() {
    vector<thread> philosophers;

    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        sem_init(&forks[i], 0, 1);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        philosophers.push_back(thread(philosopher, i));
    }

    for (thread &philosopher_thread : philosophers) {
        philosopher_thread.join();
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        sem_destroy(&forks[i]);
    }

    return 0;
}
