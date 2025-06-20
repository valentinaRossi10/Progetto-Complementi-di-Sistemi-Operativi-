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
    FCB* dest_fcb;
    while(token != NULL){
        if (strcmp(".", token) == 0) {
            token = strtok(NULL, "/");
            continue;
        }
        else if (strcmp("..", token) == 0) {
            if (currentFCB->directory == -1) {
                // if you are in the root directory and execute cd ..
                // it does not raise any error, it simply stays there
                token = strtok(NULL,"/");
                continue;
            }else{
                
                currentFCB = (FCB*) goto_memoryarea(disk_layout, currentFCB->directory);
                vr_shell_update_path(token, up); // to update the prompt string
                token = strtok(NULL,"/");
                continue;
            }
        }else {
           // printf("current->first %d\n", currentFCB->first_index);
            int fcb_index = vrFS_dir_search(disk_layout, currentFCB->first_index, token);

            if (fcb_index == FILE_NOT_FOUND){
                printf("cd: %s: File o directory non esistente\n",token);
                executing_command->return_value = ERR_FILE_NOT_FOUND;
                return;
            }
            dest_fcb = (FCB*)goto_memoryarea(disk_layout,fcb_index);

            if (!dest_fcb->is_directory){ // check that it is a directory 
                printf("cd: %s: Non è una directory\n", dest_fcb->filename);
                executing_command->return_value = ERR_FILE_NOT_A_DIR;
                return;
            }
            
            currentFCB = dest_fcb;
            vr_shell_update_path(dest_fcb->filename, down);

            token = strtok(NULL,"/");

        }
    }
    executing_command->return_value = SUCCESS;
}