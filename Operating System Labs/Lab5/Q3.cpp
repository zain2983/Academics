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
    int pipe1[2]; 
    int pipe2[2]; 
    
    // Checking to see if there is any kind of error in the creation of pipe
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe");
        exit(1);
    }
    
    pid_t pid = fork();
    if (pid == 0) {
        close(pipe1[1]); 
        close(pipe2[0]); 

        char msg[256];
        ssize_t bytesRead = read(pipe1[0], msg, sizeof(msg));
        for (int i = 0; i < bytesRead; ++i) {
            if (islower(msg[i])) {
                msg[i] = toupper(msg[i]);
            } else if (isupper(msg[i])) {
                msg[i] = tolower(msg[i]);
            }
        }
        write(pipe2[1], msg, bytesRead);

        close(pipe1[0]);
        close(pipe2[1]);
    } 
    else {
        close(pipe1[0]);
        close(pipe2[1]); 
        string msg1;
        cout << "Enter message: ";
        getline(cin, msg1);
        write(pipe1[1], msg1.c_str(), msg1.size());
            
        char msg2[256];
        ssize_t bytesRead = read(pipe2[0], msg2, sizeof(msg2));
        cout << "Modified Return Message: " << msg2 << endl;
        close(pipe1[1]);
        close(pipe2[0]);
        wait(nullptr);
    }
    return 0;
}























