#include <iostream>
#include <unistd.h>
#include <sys/types.h>
using namespace std;

int main() {
    pid_t pid; // Process ID
    pid = fork();

    if (pid < 0) {
    cout << "Fork failed!" <<endl;
    return 1;
    } 
    
    else if (pid == 0) {
    int number;
    cout << "Child Process: Enter a number: ";
    cin >> number;
    
    if (number % 2 == 0) {
    cout << "Child Process: " << number << " is even." << std::endl;
    } 
    else {
    cout << "Child Process: " << number << " is odd." << std::endl;
    }
    } 
    
    else {
        int number;
        cout << "Parent Process: Enter a number: ";
        cin >> number;
        cout << "Parent Process: You entered " << number <<endl;
    }

return 0;
}