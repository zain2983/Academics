#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
using namespace std;

int main() {
    const char *pipeName = "mypipe";

    mkfifo(pipeName, 0666);

    int pipe_fd = open(pipeName, O_RDONLY);

    while (true) {
        char buffer[100];

        ssize_t bytesRead = read(pipe_fd, buffer, sizeof(buffer));
        buffer[bytesRead] = '\0'; 

        char op;
        double op1, op2;

        sscanf(buffer, "%c %lf %lf", &op, &op1, &op2);

        double otp = 0;
        switch (op) {
            case '+':
                otp = op1 + op2;
                break;
            case '-':
                otp = op1 - op2;
                break;
            case '*':
                otp = op1 * op2;
                break;
            case '/':
                otp = op1 / op2;
                break;
            default:
                cout << "Invalid operator" << endl;
                break;
        }

        // Print the result
        cout << "Output : " << op1 << " " << op << " " << op2 << " = " << otp << endl;
    }

    // Close and remove the named pipe
    close(pipe_fd);
    unlink(pipeName);

    return 0;
}

