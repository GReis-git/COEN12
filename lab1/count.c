#include <stdio.h>
#include <stdlib.h>

// Maxiumum word length, anything longer than this will be omitted from result
#define MAX_WORD_LENGTH 30

int main(int argc, char* argv[]) {
    
    // create variables
    char buff[MAX_WORD_LENGTH+1];
    int counter = 0;
    FILE *file;
    
    // check if file is null or incorrect args
    if (argc != 2) {
        printf("%s","Too few arguments.\n");
        return 0;
    }
    else if ((file = fopen(argv[1], "r")) == NULL) {
        printf("%s", "File Not Found, Exiting.\n");
        return 0;
    }
    else {
        // run through each string until EOF
        while(fscanf(file, "%s", buff)== 1) {
            counter++;
        }
    }
    // print and exit
    printf("%d words\n", counter);
    
    fclose(file);
    return 0;
    
}
