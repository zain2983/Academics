#include <iostream>
#include <fstream>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
using namespace std;


int main() {
    key_t shm_key = ftok("/tmp", 'X');
    int shm_id = shmget(shm_key, sizeof(int) * 5, IPC_CREAT | 0666);
    int* arr = static_cast<int*>(shmat(shm_id, nullptr, 0));

    pid_t pid =fork();    

    if (pid==-1){
        cout<<"Error ! "<<endl;
        return 0;
    }
    if(pid==0){
        cout << "Enter 5 numbers" << endl;
         for(int i=0;i<5;i++){
             cin >> arr[i];
         }
    }
    else{
        wait(nullptr);
        cout<<"Square of the array"<<endl;
        for(int i=0 ; i<5 ; i++ ){
            arr[i] = arr[i] * arr[i];
            cout << arr[i] ;
            cout << " ";
        }
        cout << endl ;
    }
    return 0;
}
