#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <cstring>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return -1;
    }

    ifstream file(argv[1]);
    if (!file) {
        cerr << "File is invalid" << endl;
        return 1;
    }

    char thisChar[2];
    char* sharedMemory;
    sem_t* semaphore;

    int sID = shmget(133, 1024, 0666 | IPC_CREAT | IPC_EXCL);
    semaphore = (sem_t*)shmat(sID, nullptr, 0);
    int id = shmget(134, 1024, 0666 | IPC_CREAT | IPC_EXCL);
    sharedMemory = (char*)shmat(id, nullptr, 0);

    sharedMemory = (char*)malloc(21);
    int i = 0;

    do {
        sharedMemory[0] = '\0';
        for (i = 0; i < 20; i++) {
            file.get(thisChar[0]);
            thisChar[1] = '\0';
            strcat(sharedMemory, thisChar);
            if (sharedMemory[i] == '$') {
                sharedMemory[i + 1] = '\0';
                break;
            }
        }
        sem_init(semaphore, 1, 0);
        cout << "Press enter to print read " << endl;
        cin.ignore();
        sem_post(semaphore);
    } while (sharedMemory[i] != '$');

    free(sharedMemory);
    sem_destroy(semaphore);
    shmdt(sharedMemory);
    shmdt(semaphore);
    shmctl(id, IPC_RMID, nullptr);
    shmctl(sID, IPC_RMID, nullptr);

    return 0;
}
