#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;
int main() {
     int num_processes = 4;
    for (int i = 0; i < num_processes; ++i) {
        pid_t child_pid = fork();

        if (child_pid == -1) {
            // Error occurred during fork
            cout << "Fork failed." << endl;
            return 1;
        } else if (child_pid == 0) {
            // Child process
            cout << "Child process " << getpid() << " is executing." << endl;
            cout << "Child process " << getpid() << " is done." << endl;
            return 0;
        }
    }
    // Parent process
    cout << "Parent process " << getpid() << " is waiting for child processes." << endl;
    for (int i = 0; i < num_processes; ++i) {
         wait(nullptr);
    }
    cout << "All child processes have completed." <<endl;

    return 0;
}
