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
        cout << "Child process " << getpid() << " is executing." <<endl;
        execlp("cp", "cp", "source_file.txt", "destination_file.txt", nullptr);
        execlp("mkdir", "mkdir", "test_directory", nullptr);
        execlp("rmdir", "rmdir", "test_directory", nullptr);
        execlp("ls", "ls", nullptr);

        cout << "execlp failed." << endl;
        return 1;
    } else {
        // Parent process
        wait(nullptr);
        cout << "Parent process " << getpid() << " is waiting for the child process." <<endl;
    }

    return 0;
}
