#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to check if a word contains at least one vowel
int contains_vowel(const char *word) {
    const char vowels[] = "aeiouAEIOU";
    for (int i = 0; word[i] != '\0'; i++) {
        if (strchr(vowels, word[i]) != NULL) {
            return 1;  // The word contains at least one vowel
        }
    }
    return 0; 
}

// Function to reverse a string
void reverse_string(char *word) {
    int len = strlen(word);
    for (int i = 0; i < len / 2; i++) {
        char temp = word[i];
        word[i] = word[len - i - 1];
        word[len - i - 1] = temp;
    }
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
        if (contains_vowel(word)) {
            reverse_string(word);  // Invert the word if it contains a vowel
        }
        fprintf(outputFile, "%s ", word);  // Write the word to the output file
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("Content has been written to Output_File.txt with inverted words.\n");

    return EXIT_SUCCESS;
}

