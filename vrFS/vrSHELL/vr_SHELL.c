#include "vr_SHELL.h"
#include <unistd.h>
#include <string.h>

char* path;
int path_size;

void vr_shell_init(){
    vrSHELL_mappings();
    path = (char*)malloc(1000);
    path_size = 0;
}

void vr_shell_prompt(){
    char* hostname = (char*)malloc(100);
    assert(gethostname(hostname,100) == 0 && "failed to get hostname");
    printf("%s@%s:~%s$", getenv("LOGNAME"), hostname, path);
}



void vr_shell_update_path(char* new_path, Direction direction){
    // function to update the path showed by the prompt
    // needs to be executed whenever we change our current directory 
    //this means every time we execute a cd command
   
    if (direction == up){
        // if we are going up in the directory tree 
        // we need to delete the last token of the path
        int removed = 0;
        int i = path_size-1;
        
        while(path[i] != '/'){
            path[i] = '\0';
            i--;
            removed++;
        }
        path[i] = '\0';
        removed++;
        path_size-= removed;
    }else{
        char* formatted_path = (char*)malloc(101);
        formatted_path[0]= '/';
        formatted_path[1] = '\0';
        strcat(formatted_path, new_path);
        strcat(path, formatted_path);
        path_size = strlen(path);

    }
}

int vr_shell_interpreter(char* cmd){

}