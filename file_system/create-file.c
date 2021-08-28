#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>


int main(int argc, char* argv[]){
    if(argc <2){
        printf("Please specify exactly 1 argument\n");
        return -1;
    }else {
        char* name = argv[1];
        int rc = creat(name, S_IRWXU);
        assert(rc >= 0);
        return 0;
    }
}
