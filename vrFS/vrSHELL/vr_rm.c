#include "vrSHELL_commands.h"
#include "../vrFS/vrFS.h"
#include <stdio.h>
#include <string.h>


void vr_rm(){
    char* filename = (char*)malloc(MAX_FILENAME_LENGTH+1);
    
    FCB* aux_dir;
    aux_dir = currentFCB;
    strcpy(filename, (char*)executing_command->command_args[0]);

    char* token = strtok(filename,"/");
    FCB* dest_fcb;

    while(token != NULL){
        if (strcmp(".", token) == 0) {
            token = strtok(NULL, "/");
            continue;
        }
        else if (strcmp("..", token) == 0) {
            if (currentFCB->directory == -1) {
                token = strtok(NULL,"/");
                continue;
            }else{
                aux_dir = (FCB*)goto_memoryarea(disk_layout, aux_dir->directory);
                
                token = strtok(NULL,"/");
                continue;
            }
        }else {
            int fcb_index = vrFS_dir_search(disk_layout, aux_dir->first_index, token);
            if (fcb_index == FILE_NOT_FOUND){
                printf("rm: %s: File o directory non esistente\n",token);
                executing_command->return_value = ERR_FILE_NOT_FOUND;
                return;
            }
            dest_fcb = (FCB*)goto_memoryarea(disk_layout, fcb_index);

            if (dest_fcb->is_directory){
                aux_dir = dest_fcb;
                token = strtok(NULL,"/");
                continue;
            }else{
                if (strtok(NULL,"/") != NULL){ //trying to access a file as if it was a directory
                    printf("rm: %s: File o directory non esistente\n", token);
                    executing_command->return_value = ERR_FILE_NOT_FOUND;
                    return;
                }
                break;
            }
        }
    }
    int x = vrFS_remove_file(disk_layout, dest_fcb);

    if (x == DIRECTORY_NOT_EMPTY){
        executing_command->return_value = DIRECTORY_NOT_EMPTY;
        printf("rm: %s: directory non vuota\n", dest_fcb->filename);
    }
    else executing_command->return_value = SUCCESS;

}

