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


    int sum = 0;
    for(int i=0;i<sz;i++){ sum += val[i];}
    
    int avg = sum / sz;
    
    cout << "The sum is : " << sum << endl ; 
cout << "The avg is : " << avg << endl ; 
    
return 0;
}
