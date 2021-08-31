#include <unistd.h>
#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <signal.h>
#include <sys/types.h>
#include "tokenizer.h"


#define NUMBER_OF_COMMANDS 3

typedef void* (*command_ptr)(struct tokens* tokens);


char* get_pwd(){
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        return NULL; 
    }else{
        return strdup(cwd); 
    }
}

void* pwd_command(struct tokens* tokens){
    char* pwd_result = get_pwd();
    if(pwd_result == NULL){
        printf("Couldn't invoke pwd command correctly.\n");
    }else{
        printf("%s\n", pwd_result);
    }
    free(pwd_result);
    return NULL;
}


void cd_to_path(char* path){
      if (chdir(path) == 0){
            pwd_command(NULL);
      }else{
         perror("chdir() error");
      }
}

void ls(char* path){
    DIR* current_dir = opendir(path);
    struct dirent* temp_dirent;
    while( (temp_dirent = readdir(current_dir)) != NULL ){
        printf("%s\n",temp_dirent->d_name);
    }
    closedir(current_dir);
}

void* cd_command(struct tokens* tokens){
    int length = get_number_of_tokens(tokens);
    if(length == 1){
        cd_to_path("/home");
    }else if(length == 2){
        cd_to_path(get_nth_token(1,tokens));
    }else{
        printf("Incorrect invocation of cd command\n");
    }
}

void* ls_command(struct tokens* tokens){
    int length = get_number_of_tokens(tokens);
    if(length == 1){
        ls(".");
    }else if(length == 2){
        ls(get_nth_token(1, tokens));
   }else{
        printf("Couldn't invoke ls command properlly.\n");
    }
}

struct fn_map{
    char* title;
    command_ptr cmd_function;                        
};

struct fn_map cmd_functions[] = { 
{ .title = "pwd", .cmd_function = &pwd_command},
{ .title = "cd", .cmd_function = &cd_command},
{ .title = "ls", .cmd_function = &ls_command}};  

command_ptr get_function(char* cmd_title){
    for(int i=0; i<NUMBER_OF_COMMANDS; i++){
        if(strcmp(cmd_title, cmd_functions[i].title) == 0){
            return cmd_functions[i].cmd_function;
        }
    }
    return NULL;
}


void handle_program_invocation(struct tokens* tokens){
    int pid = fork();    
    if(pid == 0){
        execv(get_nth_token(0, tokens), tokens->tokens);
    }else if(pid > 0){
        
    }else{
        printf("Error invokig command %s\n", get_nth_token(0, tokens));
    }
}

int main(int argc, char *argv[]) {
    printf("Welcome to Shell\n");
    static char line[4096];
    char* pwd = get_pwd();
    printf("%s >", pwd);
    free(pwd);
    while(fgets(line, 4096, stdin)){
        line[strcspn(line, "\n")] = 0;
        struct tokens* tokens = tokenize(line);
        command_ptr fnc = get_function(get_nth_token(0, tokens)); 
        if(fnc == NULL){
            handle_program_invocation(tokens);    
        }else{
            fnc(tokens);
        }
        destroy_tokens(tokens);
        pwd = get_pwd();
        printf("%s >", pwd);
        free(pwd);
    }
    return 0;
}
