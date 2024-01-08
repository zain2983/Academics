#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include<sys/types.h>
using namespace std;
int main(int argc,char *arg[]){
if (argc==1){
cout<<"No File Exists"<<endl;
return 0;
}
else {

 int inputFile = open("inp.txt", O_RDONLY);
    if (inputFile == -1) {
        cout << "Error opening input file" <<endl;
        return 0;
    }

    int outputFile = open("t1_output.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (outputFile == -1) {
        cout << "Error opening output file" <<endl;
        close(inputFile);
        return 0;
    }

    char buffer[1024];
    ssize_t bytesRead;

    while ((bytesRead = read(inputFile, buffer, sizeof(buffer))) > 0) {
        for (ssize_t i = 0; i < bytesRead; ++i) {
            cout<<buffer[i];
            }
           
        }
   

    close(inputFile);
    close(outputFile);
}
return 0;
}
