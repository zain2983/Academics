#include <iostream>
#include <fstream>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>

void removeNonAlphabets(const char *inputFileName, const char *outputFileName) {
    int inputFile = open(inputFileName, O_RDONLY);
    if (inputFile == -1) {
        std::cerr << "Error opening input file" << std::endl;
        return;
    }

    int outputFile = open(outputFileName, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (outputFile == -1) {
        std::cerr << "Error opening output file" << std::endl;
        close(inputFile);
        return;
    }

    char buffer[1024];
    ssize_t bytesRead;

    while ((bytesRead = read(inputFile, buffer, sizeof(buffer))) > 0) {
        for (ssize_t i = 0; i < bytesRead; ++i) {
            if (isalpha(buffer[i])) {
                write(outputFile, &buffer[i], 1);
            }
        }
    }

    close(inputFile);
    close(outputFile);
}

int main() {
    const char *inputFileName = "inp_file.txt";
    const char *outputFileName = "output.txt";

    removeNonAlphabets(inputFileName, outputFileName);

    std::cout << "Non-alphabets removed and written to output file." << std::endl;

    return 0;
}