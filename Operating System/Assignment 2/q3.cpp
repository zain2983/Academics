#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

bool check_prime(int n) {
  bool is_prime = true;

  // Excludign 0 and 1 since they are not prime numbers
  if (n == 0 || n == 1) {
    is_prime = false;
  }

  for (int i = 2; i <= n / 2; ++i) {
    if (n % i == 0) {
      is_prime = false;
      break;
    }
  }
  return is_prime;
}

int main() {
    int lwr_range;
    int upr_range;
    cout<<"Enter the upper range: "<<endl;      cin>> upr_range;
    cout<<"Enter the lower range: "<<endl;      cin>> lwr_range;
    
    pid_t pid = fork();

    if (pid == 0) { 
        for (int i = lwr_range ; i <= upr_range ; i++) {
            if (check_prime(i)) {
                cout << i <<" is prime" << endl;
            }
        }
    }
    else if (pid==-1){
         cout<< "Child Terminated" << endl;
            return 0;
    }
    else { 
        wait(nullptr);
        cout << "The range was " << lwr_range << " - " << upr_range << endl;
        cout << "Child process completed" << endl;
    } 
    
    return 0;
}
