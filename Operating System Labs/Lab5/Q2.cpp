#include <iostream>
#include <fstream>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
using namespace std;

bool isAlphabetic(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

void read_func(const char* fileName, char* sharedMemory) {
    ///////////////////////////////////////////////////
    // Reading data from the input file 
    ifstream inputFile(fileName);
    if (!inputFile) {
        cerr << "Error : Cannot open Input File" << endl;
        exit(1);
    }
    ///////////////////////////////////////////////////
    // Now we're writing the data in the shared memory 
    string data;
    char ch;
    while (inputFile.get(ch)) {
        data += ch;
    }
    strcpy(sharedMemory, data.c_str());
    inputFile.close();
}


// Funtion to convert small alphabets to capital and vice versa
// It also removes all the numbers in the file 
void write_func(char* sharedMemory, const char* fileName) {
    ofstream otpfile(fileName);
    if (!otpfile) {
        cerr << "Error : Cannot open Output File" << endl;
        exit(1);
    }
    


    string data(sharedMemory);
    for (char& c : data) {
        if (isAlphabetic(c)) {
            if (islower(c)) { c = toupper(c); } 
            else { c = tolower(c); }
        } 
        else if (isdigit(c)) {
            c = ' ';
        }
    }
    otpfile << data;
    otpfile.close();
}



int main(int argc, char* argv[]) {

    if (argc < 2) {
        cout << "Error : You didn't input the file name ! " << endl;
        cout << "You need to enter the name of the input file as an argument";
        return 1;
    }

    const char* fileName = argv[1];
    key_t shm_key = ftok("/tmp", 'X');
    int shm_id = shmget(shm_key, 1024, IPC_CREAT | 0666);
    char* sharedMemory = static_cast<char*>(shmat(shm_id, nullptr, 0));
    pid_t pid = fork();
    
     if (pid == 0) {
        read_func(fileName, sharedMemory);
        exit(0);
    } else {
        wait(nullptr);
        write_func(sharedMemory, fileName);
        cout << "File Updated !" << endl;
    }
    return 0;
}


















