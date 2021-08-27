#include <stdio.h>
#include <stddef.h>
#include <ctype.h>
#include <stdbool.h>
#include "core_wc.c"

int main(int argc, char* argv[]){
    if(argc == 2){
        char* fileName = argv[1];
        FILE* filePointer = fopen( fileName, "r");
        Tuple result = countForFile(filePointer);
        printf("*****File: %s*****\n", fileName);
        printf("Number of Characters = %d\n", result.numCharacters);
        printf("Number of Lines = %d\n", result.numLines);
        printf("Number of words = %d\n", result.numWords);
    }else if(argc == 1){
        printf("%s\n", argv[0]);
    }
    return 0;
}
