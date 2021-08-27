#include <assert.h>
#include <stdio.h>
#include "../program/core_wc.c"


int main(int argc, char *argv[]) {
    FILE *file = fopen("./tests/testFiles/test1.txt", "r");
    if (file == NULL) {
        printf("Incorrect file path specified\n");
        return -1;
    }
    Tuple result = countForFile(file);
    printf("%d\n", result.numLines);
    assert(9 == result.numCharacters);
    assert(4 == result.numLines);
    assert(5 == result.numWords);
    return 0;
}
