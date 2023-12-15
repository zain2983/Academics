#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
using namespace std;

int main() {

    const char *pipeName = "mypipe";

    int pipe_fd = open(pipeName, O_WRONLY);

    while (true) {
        string input;
        cout << "Enter operator and numbers (e.g., + 4 10) : ";
        getline(cin, input);
        
        write(pipe_fd, input.c_str(), input.length());
    }


    close(pipe_fd);

    return 0;
}

