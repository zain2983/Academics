#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;
int main() {
    pid_t child_pid = fork();

    if (child_pid == -1) {
        // Error occurred during fork
        cout << "Fork failed." <<endl;
        return 1;
    } else if (child_pid == 0) {
        // Child process
        cout << "Child process is executing." << endl;

        if (execlp("ls", "ls", "-l", nullptr) == -1) {
            // execlp failed
            cout<< "execlp failed." << endl;
            return 1;
        }
    } else {
        // Parent process
        cout << "Parent process  is waiting for the child process." <<endl;
        int status;
        pid_t terminated_pid = wait(nullptr);
        if (terminated_pid == -1) {
            cout << "Error occurred while waiting for the child process." <<endl;
            return 1;
        }
        if (WIFEXITED(status)) {
            cout << "Child process exited "<< endl;
        }
    }
    return 0;
}
