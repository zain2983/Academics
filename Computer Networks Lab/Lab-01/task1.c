#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char ch;

    file = fopen("Input File.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }
    
    printf("\n");  

    fclose(file);

    return EXIT_SUCCESS;
}

