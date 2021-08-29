#include <dirent.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INODE_NUM 30


int get_size_of_number(ino_t number){
    int result = 0; 
    ino_t left_over = number;
    while((left_over = left_over / 10) != 0){
        result ++;
    }
    return result;
}

char* convert_inode_to_string(ino_t number){
    int len = get_size_of_number(number);
    char str[len +1];
    str[len] = '/0';
    sprintf(str, "%ld", number);
    return strdup(str);
}

int main(int argc, char* argv[]){
    bool t_flag=false;
    if(argc == 2){
        if(strcmp("-t", argv[1]) == 0){
            t_flag = true;
        }
    }
    DIR* current_dir = opendir(".");
    struct dirent* temp_dirent;
    while( (temp_dirent = readdir(current_dir)) != NULL ){
        char* inode_num = convert_inode_to_string(temp_dirent->d_ino); 
        printf("%s%s\n", t_flag ? strcat(inode_num, "  "): "",temp_dirent->d_name);
        free(inode_num);
    }
    closedir(current_dir);
    return 0;
}
