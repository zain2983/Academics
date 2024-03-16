#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <omp.h>
using namespace std;

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
//   My code on my system was only working when i used 3 rows 
//   because my system has 4 threads and i think that after 1 master thread 
//   i have only left 3 threads so therefore if i use more rows columns
//   than 3 my sorting doesnt work correctly. It sorts the first 3 then 
//   it sorts the next 3 and so on . However sometimes the code works fine
//   even with 6 rows 
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

// For generating random numbers
int generateRandom(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Quick Sort algorithm
void quickSort(vector<int>& arr, int low, int high, bool ascending) {
    if (low < high) {
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if ((ascending && arr[j] < pivot) || (!ascending && arr[j] > pivot)) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        int partitionIndex = i + 1;
        #pragma omp task
        quickSort(arr, low, partitionIndex - 1, ascending);
        #pragma omp task
        quickSort(arr, partitionIndex + 1, high, ascending);
    }
}

// Function to sort each row of the matrix using Quick Sort
void sortRows(vector<vector<int>>& matrix, bool ascending) {
    #pragma omp parallel for
    for (size_t i = 0; i < matrix.size(); i++) {
        quickSort(matrix[i], 0, matrix[i].size() - 1, ascending);
    }
}

// Basic product of the matrix
long long matrixProduct(const vector<vector<int>>& matrix) {
    long long x = 1;
    for (const auto& i : matrix) {
        for (int value : i) {
            x *= value;
        }
    }
    return x;
}

// For printing the matrix 
void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int value : row) {
            cout << value << " ";
        }
        cout <<endl;
    }
}   

int main() {
    int m, n;
    cout << "Enter number of rows (m): ";
    cin >> m;
    cout << "Enter number of columns (n): ";
    cin >> n;

    vector<vector<int>> matrix(m, vector<int>(n));
    srand(time(nullptr));
    for (auto& row : matrix) {
        for (int& value : row) {
            value = generateRandom(1, 10);
        }
    }

    cout << "Original Matrix:" << endl;
    printMatrix(matrix);

    bool ascending = true;

    #pragma omp parallel
    {
        #pragma omp single
        {
            sortRows(matrix, ascending);
        }
    }

    cout << "Sorted Matrix:" <<endl;
    printMatrix(matrix);

    long long product = matrixProduct(matrix);
    cout << "Product : " << product << endl;

    return 0;
}
