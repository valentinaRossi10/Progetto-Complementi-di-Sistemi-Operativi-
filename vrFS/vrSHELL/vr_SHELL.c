#include "vr_SHELL.h"
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>


char* path;
int path_size;
FCB* currentFCB;
DiskLayout disk;
DiskLayout* disk_layout;
int format_done = 0;

void vr_shell_init(){
    //executes the mappings 
    //initializes the path and path_size variables
    disk_layout = &disk;
    currentFCB = NULL;
    vrSHELL_mappings();
    path = (char*)malloc(1000);
    path_size = 0;
}

void vr_shell_prompt(){
    // function that prints the prompt of the shell 
    char* hostname = (char*)malloc(100);
    assert(gethostname(hostname,100) == 0 && "failed to get hostname");
    printf("%s@%s:~%s$ ", getenv("LOGNAME"), hostname, path);
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
    //parsing of the command string association to the corresponding command number
    //execution of command_wrapper
    char* safe_copy = (char*)malloc(strlen(cmd)+1); // strtok modifies the string so we make a copy 
    strcpy(safe_copy, cmd);
    char* token = strtok(safe_copy, " \t\n"); 
    int cmd_num = -1;
    if (strcmp(token,"format")!= 0 && !format_done){
        printf("disco non pronto, eseguire format <filename> <size>\n");
        return DISK_NOT_READY;
    }

    if (strcmp(token,"cd") == 0){
        cmd_num = SHELL_CD;
        char* arg = strtok(NULL, " \t\n" );
        command_wrapper(SHELL_CD, arg);

    }else if (strcmp(token, "append") == 0){
        cmd_num = SHELL_APPEND;
        char* arg1 = strtok(NULL, " \t\n");
        char* arg2 = strtok(NULL, "\n");
        command_wrapper(SHELL_APPEND, arg1, arg2);


    }else if (strcmp(token,"cat") == 0){
        cmd_num = SHELL_CAT;
        char* arg = strtok(NULL, " \t\n" );
        command_wrapper(SHELL_CAT, arg);


    }else if (strcmp(token, "close") == 0){
        cmd_num = SHELL_CLOSE;
        command_wrapper(SHELL_CLOSE);


    }else if (strcmp(token, "format") == 0){
        cmd_num = SHELL_FORMAT;
        char* arg = strtok(NULL, " \t\n" );
        char* arg2 = strtok(NULL, " \t\n" );
        int arg2_i = atoi(arg2);
        command_wrapper(SHELL_FORMAT, arg, arg2_i);


    }else if (strcmp(token, "ls") == 0){
        char* arg = strtok(NULL, " \t\n" );
        if ( arg == NULL) {
            cmd_num = SHELL_LS;
            command_wrapper(SHELL_LS);
        }
        else{
            cmd_num = SHELL_LS_WITH_ARG;
            command_wrapper(SHELL_LS_WITH_ARG, arg);
            
        }
        
    }else if(strcmp(token, "mkdir")== 0){
        cmd_num = SHELL_MKDIR;
        char* arg = strtok(NULL, " \t\n" );
        command_wrapper(SHELL_MKDIR, arg);        

    }else if (strcmp(token,"rm") == 0){
        cmd_num = SHELL_RM;
        char* arg = strtok(NULL, " \t\n" );
        command_wrapper(SHELL_RM, arg); 

    } else if (strcmp(token,"touch") == 0){
        cmd_num = SHELL_TOUCH;
        char* arg = strtok(NULL, " \t\n" );
        command_wrapper(SHELL_TOUCH, arg); 

    }else {
        printf("comando %s non trovato\n", token);
        return -1;
    }
    return cmd_num;
}


void vr_shell_loop(){
    vr_shell_init();
    while(1){
        vr_shell_prompt();
        char line[100];
        memset(line, '\0', 100);
        fgets(line, 100, stdin);
        if (strtok(line, "\n") == NULL) continue; //nothing was written

        int x = vr_shell_interpreter(line);
        

        if (x == SHELL_CLOSE) {
            printf("closing the shell...\n");
            break;
        }else if (x == SHELL_FORMAT && executing_command->return_value == SUCCESS){
            format_done = 1;
        }

        /*int pid = fork();
        int x;
        if (pid == -1){
            break;
        }else if (pid == 0){
            x = vr_shell_interpreter(line);
            if (x == SHELL_CLOSE) {
                printf("closing the shell...\n");
                break;
            exit(0);
        }

        }
        wait(NULL);
        */
    }

}


int main(){
    vr_shell_loop();
}