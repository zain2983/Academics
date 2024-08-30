#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main() {
    FILE *inputFile, *outputFile;
    char ch;

    inputFile = fopen("Input File.txt", "r");
    if (inputFile == NULL) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    outputFile = fopen("Output File.txt", "w");
    if (outputFile == NULL) {
        perror("Error creating output file");
        fclose(inputFile); 
        return EXIT_FAILURE;
    }

    while ((ch = fgetc(inputFile)) != EOF) {
        if (isdigit(ch)) {
            fputc(ch, outputFile);
        }
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("Integers have been written to Output File.txt\n");

    return EXIT_SUCCESS;
}

