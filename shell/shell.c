#include <unistd.h>
#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"

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

struct fn_map{
    char* title;
    command_ptr cmd_function;                        
};


struct fn_map cmd_functions[] = { { .title = "pwd", .cmd_function = &pwd_command} };  

command_ptr get_function(char* cmd_title){
    return cmd_functions[0].cmd_function;
}

int main(int argc, char *argv[]) {
    printf("Welcome to Shell\n");
    static char line[4096];
    printf(">");
    while(fgets(line, 4096, stdin)){
        struct tokens* token = tokenize(line);
        get_function(line)(token); 
        destroy_tokens(token);
        printf(">");
    }
    return 0;
}
