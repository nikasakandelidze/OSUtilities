
#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"


int main(int argc, char *argv[]) {
    printf("Welcome to Shell\n");
    static char line[4096];
    printf(">");
    while(fgets(line, 4096, stdin)){
        struct tokens* token = tokenize(line);
        for(int i=0; i<token->log_len; i++){
            printf("%s\n", token->tokens[i]); 
        }
        destroy_tokens(token);
        printf(">");
    }
    return 0;
}
