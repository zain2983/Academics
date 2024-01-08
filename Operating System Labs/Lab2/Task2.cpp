#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include<sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;
int main(int argc,char *arg[]){

    //   Conversion from char to int 
    int sz=argc-1;
    int val[sz];
  
    for(int i=0;i<sz;i++){  val[i]=atoi(arg[i+1]);  }
    
    // for(int i=0;i<sz;i++){ cout << val[i] << endl ; }

    //Sorting
    int n=sz;
    int temp;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (val[i] > val[j]) {
                temp = val[i];
                val[i] = val[j];
                val[j] = temp;
            }
        }	
    }

    //print sorted array elements
    cout << "Sorted (Ascending Order) Array elements:" << endl;
    for (int i = 0; i < n; i++)
        cout << val[i] << "\t";
    cout << endl;
    
    
return 0;
}
