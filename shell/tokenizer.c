#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"

#define INIT_SIZE 20

void copy_word(char* source, tokens* destination_tokens){
   int log_len = destination_tokens -> log_len; 
   if ( log_len == destination_tokens -> alloc_len){
        //todo: reallocation of bigger memory
   }else{
       char* string_in_heap = strdup(source);
       memcpy(&(destination_tokens->tokens[log_len]), &string_in_heap, sizeof(char**));
       destination_tokens -> log_len ++;
   }
}

tokens* tokenize(const char* line){
    tokens* tokens_result = malloc(sizeof(tokens));
    tokens_result -> log_len = 0;
    tokens_result -> alloc_len = INIT_SIZE;
    tokens_result -> tokens = malloc(tokens_result -> alloc_len * sizeof(tokens));
    size_t line_length = strlen(line);
    char token[4096];
    int index_in_token =0;
    for(int i=0; i<line_length; i++){
        char current_char = line[i];
        if(isspace(current_char) || i == line_length -1){
            if(i == line_length - 1){
                token[index_in_token++] = current_char;
            }
            token[index_in_token]='\0';
            copy_word(token, tokens_result);            
            index_in_token=0;
        }else{
            token[index_in_token++] = current_char;
        }
    }
    return tokens_result;
}

size_t get_number_of_tokens(struct tokens *tokens){
    return tokens->log_len;
}

char *get_nth_token(size_t n, struct tokens *tokens){
    return tokens -> tokens[n];
}

void destroy_tokens(struct tokens *tokens){
    for(int i=0; i<tokens->log_len; i++){
        free(tokens->tokens[i]);
    }
    free(tokens->tokens);
    free(tokens);
}

