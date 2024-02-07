#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

const int MAX_INPUT_SIZE = 100;
const int MAX_ARGS = 100;

void tokenize(const string& input, char *args[]) {
    char *token = strtok(const_cast<char*>(input.c_str()), " \t\n");
    int i = 0;
    while ( (token != nullptr) && (i < MAX_ARGS - 1) ) {
        args[i++] = token;
        token = strtok(nullptr, " \t\n");
    }
    args[i] = nullptr;
}



int main() {
    char input[MAX_INPUT_SIZE];
    char *args[MAX_ARGS];
    cout << "Press 'exit' to quit the shell."<<endl;
    
    while (true) {
        cout << "Custom Shell: ";
        
        cin.getline(input, sizeof(input));
        if (string(input) == "exit") { break; }
        
        tokenize(input, args);
        pid_t pid = fork();
        
        if (pid == -1) {
            cout<<"Fork failed"<<endl;
            exit(1);
        } 
        
        else if (pid == 0) {
             // wrk is used to check wheter its working or not 
             int wrk = execvp(args[0],args);
             if(wrk==-1) {
             cout<<"Error"<<endl;
             break;
             }
        } 
        else { wait(nullptr); }
    }
    
    cout << "Exit Successful" << endl;
    return 0;
}
