#include "vrSHELL_commands.h"
#include "../vrFS/vrFS.h"
#include <stdio.h>
#include <string.h>
#include "vr_SHELL.h"

void vr_cd(){


    char* filename = (char*)malloc(MAX_FILENAME_LENGTH);
    strcpy(filename,  (char*)executing_command->command_args[0]);
    
    //parsing del path 
    char* token = strtok(filename,"/");
    FCB dest_fcb;
    while(token != NULL){
        if (strcmp(".", token) == 0) {
            token = strtok(NULL, "/");
            continue;
        }
        else if (strcmp("..", token) == 0) {
            if (currentFCB->directory == NULL) {
                // observing the behavior of my shell i noticed that 
                // if you are in the root directory and execute cd ..
                // it does not raise any error, it simply stays there
                token = strtok(NULL,"/");
                continue;
            }else{
                 FCB* parent = (FCB*)malloc(sizeof(FCB));
                *parent = *(currentFCB->directory);
                currentFCB = parent;
                vr_shell_update_path(token, up);
                token = strtok(NULL,"/");
                continue;
            }
        }else {
            int x = vrFS_dir_search(disk_layout, currentFCB, &dest_fcb, token);
            if (x == FILE_NOT_FOUND){
                printf("cd: %s: File o directory non esistente\n",token);
                executing_command->return_value = ERR_FILE_NOT_FOUND;
                return;
            }
            if (!dest_fcb.is_directory){
                printf("cd: %s: Non è una directory", dest_fcb.filename);
                executing_command->return_value = ERR_FILE_NOT_A_DIR;
                return;
            }
            FCB* new_fcb = (FCB*)malloc(sizeof(FCB));
            *new_fcb = dest_fcb;
            new_fcb->directory = currentFCB;  // set parent
            currentFCB = new_fcb;  
            vr_shell_update_path(new_fcb->filename, down);

            token = strtok(NULL,"/");

        }
    }
    executing_command->return_value = SUCCESS;
}