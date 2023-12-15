#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
using namespace std;
int main() {
    int input_fd = open("input.txt", O_RDONLY);
    if (input_fd == -1) {
        cout << "Error opening input.txt" << endl;
        return -1;
    }
    int output_fd = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC);
    if (output_fd == -1) {
        cout << "Error opening output.txt" << endl;
        close(input_fd);
        return -1;
    }
    // Save the original file descriptors for stdin and stdout
    int saved_stdin_fd = dup(STDIN_FILENO);
    int saved_stdout_fd = dup(STDOUT_FILENO);
    // Duplicate input file descriptor to stdin
    if (dup2(input_fd, STDIN_FILENO) == -1) {
        cout << "Error redirecting stdin" << endl;
        close(input_fd);
        close(output_fd);
        return -1;
    }
    // Duplicate output file descriptor to stdout
    if (dup2(output_fd, STDOUT_FILENO) == -1) {
        cout << "Error redirecting stdout" << endl;
        close(input_fd);
        close(output_fd);
        return -1;
    }
    int sum = 0;
    char ch;
    while (cin.get(ch)) {
        if (ch >= '0' && ch <= '9') {
            sum += (ch - '0');
        }
    }
    cout << sum << endl;
    close(input_fd);
    close(output_fd);
    // Restore stdin and stdout to their original file descriptors
    dup2(saved_stdin_fd, STDIN_FILENO);
    dup2(saved_stdout_fd, STDOUT_FILENO);
    return 0;
}
