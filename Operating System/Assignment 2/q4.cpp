#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

void merge(int arr[], int p, int q, int r) {
  int n1 = q - p + 1;
  int n2 = r - q;
  int L[n1], M[n2];
  for (int i = 0; i < n1; i++)
    L[i] = arr[p + i];
  for (int j = 0; j < n2; j++)
    M[j] = arr[q + 1 + j];
  int i, j, k;
  i = 0;
  j = 0;
  k = p;
  while (i < n1 && j < n2) {
    if (L[i] <= M[j]) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = M[j];
      j++;
    }
    k++;
  }
  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }
  while (j < n2) {
    arr[k] = M[j];
    j++;
    k++;
  }
}

void mergeSort(int arr[], int l, int r) {
  if (l < r) {
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
  }
}

int main() {
    int arr[10]={3,8,2,4,9,11,1,5,6,3};
    int size=10; 
    int mid = size/2;
    pid_t pid=fork();
    
    if(pid==0){
        cout<<"The child process "<<getpid()<<endl;
        mergeSort(arr,0,mid-1);
    }
    else if(pid==-1){
        cout<<"The process has been terminated"<<endl;
    }
    else{
        mergeSort(arr,mid,size-1);
        wait(nullptr);
        merge(arr, 0, mid - 1, size - 1);
        for(int i=0; i<size ; i++ ){
        cout << arr[i] << " ";
    }
        cout << endl;
        cout << "The child process with PID = " <<getpid() <<" has been completed"<<endl;
    }
    return 0;
}
