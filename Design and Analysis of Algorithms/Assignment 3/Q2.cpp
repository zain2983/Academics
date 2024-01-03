#include <iostream>
using namespace std;

double x[5];

double top_down_func(int num) {
    if (num == 0) { return 1; }
    if (x[num] != 0.0) { return x[num]; } 
    else{
        double total = 0;
        for (int i = 0; i <num; i++){
            total += top_down_func(i);
        }
        x[num] = 2.0 * total /num + num;
        return x[num];
    }
}

int main() {
    // Initializing n to 4 so that we have 5 iterations  
    int n = 4;
    for (int i = 0; i <= 4; i++) {
        double result = top_down_func(i);
        cout << "C(" << i << ") = " << result << endl;
    };
    return 0;
}
