#include <unistd.h>
#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"

#define NUMBER_OF_COMMANDS 2

typedef void* (*command_ptr)(struct tokens* tokens);

void* pwd_command(struct tokens* tokens){
    char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) == NULL) {
		perror("cwd() error");
	}else{
	    fprintf(stdout, "%s\n", cwd);
    }
    return NULL;
}


void cd_to_path(char* path){
      if (chdir(path) == 0){
            pwd_command(NULL);
      }else{
         perror("chdir() error");
      }
}



void* cd_command(struct tokens* tokens){
    if(get_number_of_tokens(tokens) == 1){
        cd_to_path("/home");
    }else if(tokens -> log_len == 2){
        cd_to_path(get_nth_token(1,tokens));
    }else{
        printf("Incorrect invocation of cd command\n");
    }
}

struct fn_map{
    char* title;
    command_ptr cmd_function;                        
};

struct fn_map cmd_functions[] = { { .title = "pwd", .cmd_function = &pwd_command}, { .title = "cd", .cmd_function = &cd_command} };  

command_ptr get_function(char* cmd_title){
    for(int i=0; i<NUMBER_OF_COMMANDS; i++){
        if(strcmp(cmd_title, cmd_functions[i].title) == 0){
            return cmd_functions[i].cmd_function;
        }
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    printf("Welcome to Shell\n");
    static char line[4096];
    printf(">");
    while(fgets(line, 4096, stdin)){
        line[strcspn(line, "\n")] = 0;
        struct tokens* tokens = tokenize(line);
        command_ptr fnc = get_function(get_nth_token(0, tokens)); 
        if(fnc == NULL){
            printf("Couldn't invoke function %s\n", line);
        }else{
            fnc(tokens);
        }
        destroy_tokens(tokens);
        printf(">");
    }
    return 0;
}
