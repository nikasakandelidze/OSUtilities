#include <stdio.h>
#include <stddef.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct Tuple{
    int numWords;
    int numLines;
    int numCharacters;
} Tuple;

Tuple INIT_TUPLE = {0, 0, 0};


Tuple countForFile(FILE* file){
    char currentChar;
    Tuple tuple = INIT_TUPLE;
    bool isWord = false;
    while((currentChar = fgetc(file)) != EOF){
        tuple.numCharacters++;
        if(isalnum(currentChar)){
            isWord = true;
        }else if((isspace(currentChar) || ispunct(currentChar)) && isWord){
             tuple.numWords++;
             isWord=false;
        }else if(currentChar == '\n'){
            if(isWord){ isWord=false; }
            tuple.numLines++;
        }
        
    }
    return tuple;
}


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
