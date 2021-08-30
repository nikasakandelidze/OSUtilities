
#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tokenizer.h"


int main(int argc, char *argv[]) {
    struct tokens* token = tokenize("abc dfg hij");
    for(int i=0; i<token->log_len; i++){
     printf("%s\n", token->tokens[i]); 
    }
    return 0;
    }
