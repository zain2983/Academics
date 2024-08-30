#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int is_non_alphabet_word(const char *word) {
    for (int i = 0; word[i] != '\0'; i++) {
        if (isalpha(word[i])) {
            return 0;
        }
    }
    return 1;
}

int main() {
    FILE *inputFile, *outputFile;
    char word[100];

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

    while (fscanf(inputFile, "%s", word) != EOF) {
        if (is_non_alphabet_word(word)) {
            fprintf(outputFile, "%s\n", word);
        }
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("Non-alphabet words have been written to Output File.txt\n");

    return EXIT_SUCCESS;
}

