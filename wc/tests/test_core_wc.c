#include <assert.h>
#include <stdio.h>
#include "../program/core_wc.c"


int main(int argc, char* argv[]){
    Tuple result = countForFile(fopen("./testFiles/test1.txt", "r"));    
    assert(10 == result.numCharacters);
    assert(5 == result.numLines);
    assert(5 == result.numWords);
    
    return 0;
}
