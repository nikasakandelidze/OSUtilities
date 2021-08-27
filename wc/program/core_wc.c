#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct Tuple{
    int numWords;
    int numLines;
    int numCharacters;
} Tuple;

Tuple countForFile(FILE* file){
    char currentChar;
    Tuple tuple = {0, 0, 0};
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
