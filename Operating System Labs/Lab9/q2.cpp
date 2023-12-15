#include <iostream>
#include <fstream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <cstring>
#include <semaphore.h>
#include <sys/wait.h>
#include <stdio.h>
#include <cstdlib>

using namespace std;

int main() {
    char buffer[256]; // Buffer to store a string (assuming a reasonable maximum length)
    int sum = 0;
    int count = 0;

    int totalsum = 0;
    int totalcount = 0;
    int Average = 0;

    ifstream file1("f1.txt");
    ifstream file2("f2.txt");

    if (!file1.is_open() || !file2.is_open()) {
        cout << "Error opening the file" << endl;
        return 1;
    }

    int sharedid = shmget((key_t)123456789, sizeof(int), IPC_CREAT | 0666);
    if (sharedid < 0) {
        cout << "Shared memory creation failed" << endl;
        return 1;
    }

    int* a = (int*)shmat(sharedid, NULL, 0);
    for (int i = 0; i < 5; i++) {
        a[i] = 0;
    }

    sem_t sem;
    sem_init(&sem, 1, 1);
    pid_t pid = fork();

    if (pid == -1) {
        cout << "Fork failed." << endl;
        return 1;
    } else if (pid == 0) {
        sem_wait(&sem);
        while (file1 >> buffer) {
            int num = atoi(buffer);
            if (num != 0) {
                sum += num;
                a[0] = sum;
                cout << a[0] << " " << endl;
                count++;
            }
        }
        a[1] = count;
        cout << "==================================" << endl ;
        sem_post(&sem);
        shmdt(a);
        exit(0);
    } else {
        wait(NULL);

        pid_t pid1 = fork();

        if (pid1 == -1) {
            return 1;
        } else if (pid1 == 0) {
            sem_wait(&sem);
            while (file2 >> buffer) {
                int num = atoi(buffer);
                if (num != 0) {
                    sum += num;
                    a[2] = sum;
                    cout << a[2] << " " << endl;
                    count++;
                }
            }
            a[3] = count;
            cout << "==================================" << endl ;
            sem_post(&sem);
            shmdt(a);
            exit(0);
        } else {
            wait(NULL);
            sem_wait(&sem);
            totalsum = a[0] + a[2];
            totalcount = a[1] + a[3];
            Average = totalsum / totalcount;
            cout << "Total sum : " << totalsum << endl;
            cout << "Total count : " << totalcount << endl;
            cout << "Average : " << Average << endl;
            sem_post(&sem);
            shmdt(a);
            shmctl(sharedid, IPC_RMID, NULL);
        }
    }

    sem_destroy(&sem);

    return 0;
}
