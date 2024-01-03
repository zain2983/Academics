#include <iostream>
using namespace std;

double cachedValues[5];

double computeValue(int num) {
    if (num == 0) {
        return 1;
    }
    if (cachedValues[num] != 0.0) {
        return cachedValues[num];
    }
    else {
        double total = 0;
        for (int i = 0; i < num; i++) {
            total += computeValue(i);
        }
        cachedValues[num] = 2.0 * total / num + num;
        return cachedValues[num];
    }
}

int main() {
    int n = 4;
    for (int i = 0; i <= 4; i++) {
        double result = computeValue(i);
        cout << "C(" << i << ") = " << result << endl;
    }
    return 0;
}
