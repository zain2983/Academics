#include <iostream>
using namespace std;

float brut_force_func(int n) {
    if (n == 0) {  return 1;} 
    else {
        float result = 0;
        for (int i = 0; i < n; i++) { result +=  brut_force_func(i);  }
        float x = 2.0 * result / n + n;
        return x;
    }
}

int main() {
    // Initializing n to 4 so that we have 5 iterations  
    int n = 4;
    for (int i = 0; i <= n; i++) {
        double otp;
        otp = brut_force_func(i);
        cout << "C(" << i << ") = " << otp << endl;
    };
}