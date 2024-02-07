#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
using namespace std;

int main() {
    pid_t pid=fork();
    if( pid==0 ){ cout << "The child process " << getpid() << endl; }
    else if( pid==-1 ){ cout << "The process has been terminated" << endl; }
    else{ cout << "The child process with PID = " <<getpid() << " has been completed" << endl; }
    return 0;
}
