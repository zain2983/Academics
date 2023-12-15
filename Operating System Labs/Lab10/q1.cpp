#include <iostream>
#include <fstream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    const char* fileName = argv[1];

    int sharedid = shmget(IPC_PRIVATE, sizeof(int) * 100, IPC_CREAT | 0666);
    if (sharedid < 0) {
        cout << "Shared memory creation failed !" << endl;
        return 1;
    }

    int* sharedData = (int*)shmat(sharedid, NULL, 0);
    pid_t pid = fork();

    if (pid == -1) {
        cout << "Fork failed ! " << endl;
        return 1;
    } 
    
    
    
    
    
    else if (pid == 0) {
        ifstream file(fileName);
        if (!file.is_open()) {
            cout << "File Error" << endl;
            return 1;
        }

        char buffer[256];
        int num;
        int index = 0;

        while (file >> buffer) {
            num = atoi(buffer);
            sharedData[index++] = num;
        }

        shmdt(sharedData);
        exit(0);
    }
    
    
    
    
    
    
    
    else {
    
    
    
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
        wait(NULL); 
        pid_t pid1 = fork();
        if (pid1 == -1) {
            cout << "Fork failed !" << endl;
            return 1;
        } 


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
           
        else if (pid1 == 0) { 
            int* uniqueData = new int[100]; 
            int uniqueCount = 0;

            for (int i = 0; i < 100 && sharedData[i] != 0; i++) {
            	bool duplicate = false;
            	for (int j = 0; j < uniqueCount; j++) {
            		if (sharedData[i] == uniqueData[j]) {
                        	duplicate = true;
                        	break;
                    }
                }
                if (!duplicate) {   uniqueData[uniqueCount++] = sharedData[i]; }
            }

        
            for (int i = 0; i < uniqueCount; i++) {    sharedData[i] = uniqueData[i];   }
            sharedData[uniqueCount] = 0; 
            delete[] uniqueData;
            exit(0);
        }
        
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////         
        
         else {
            wait(NULL); 
            ofstream outFile(fileName, ios::trunc);
            if (!outFile.is_open()) {
                cout << "File Error" << endl;
                return 1;
            }
            
            for (int i = 0; i < 100 && sharedData[i] != 0; i++) {
                cout<< sharedData[i] <<" ";
                outFile << sharedData[i] << " ";
            }

            shmdt(sharedData);
            shmctl(sharedid, IPC_RMID, NULL); 
        }
        
        
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////      
        
    }
    cout << endl ; 

    return 0;
}
