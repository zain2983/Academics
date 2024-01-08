#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

int fibonacci(int n) {
    if (n <= 1) { return n;  } 
    else {  return fibonacci(n - 1) + fibonacci(n - 2);  }
}


int main() {
    pid_t pid; 
    
    pid = fork();

    if (pid < 0) {
    cout << "Fork failed!" <<endl;
    return 1;
    } 
    
    else if (pid == 0) {
      for (int i = 0; i < 15; i++) {
            int fib = fibonacci(i);
            cout << "Child: Fibonacci(" << i << ") = " << fib << endl;
      }
    }
    
    else {

        wait(NULL);
        cout << "Parent: Child process completed." <<endl;
    }
    
    return 0;
}