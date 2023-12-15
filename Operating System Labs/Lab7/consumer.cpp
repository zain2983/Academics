#include <iostream>
#include <cstring>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>

using namespace std;

int main(int argc, char* argv[]) {
    char* sharedMemory;
    sem_t* semaphore;

    int sID = shmget(133, 1024, 0);
    int id = shmget(134, 1024, 0);

    sharedMemory = (char*)shmat(sID, nullptr, 0);
    semaphore = (sem_t*)shmat(id, nullptr, 0);

    for (int i = 0; sharedMemory[i] != '$'; i++) {
        sem_wait(semaphore);
        for (int j = 0; j < 20 && sharedMemory[j] != '$'; j++) {
            cout << sharedMemory[i]; // Changed printf to cout
        }
        cout << endl;
        cout << "Press enter to return to the previous task" << endl;
        cin.ignore();
        sem_post(semaphore);
    }

    shmdt(semaphore);
    shmdt(sharedMemory);

    return 0;
}
