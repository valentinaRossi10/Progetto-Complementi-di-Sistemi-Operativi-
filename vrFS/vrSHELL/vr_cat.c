#include "vrSHELL_commands.h"
#include "../vrFS/vrFS.h"
#include <stdio.h>


void vr_cat(){
    char* filename = (char*)malloc(MAX_FILENAME_LENGTH+1);
    
    FCB* file_to_cat;
    file_to_cat = currentFCB;
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
                file_to_cat = (FCB*)goto_memoryarea(disk_layout, file_to_cat->directory);
                token = strtok(NULL,"/");
                continue;
            }
        }else {
            int fcb_index = vrFS_dir_search(disk_layout, file_to_cat->first_index, token);
            if (fcb_index == FILE_NOT_FOUND){
                printf("cat: %s: File o directory non esistente\n",token);
                executing_command->return_value = ERR_FILE_NOT_FOUND;
                return;
            }
            dest_fcb = (FCB*) goto_memoryarea(disk_layout, fcb_index);
            if (dest_fcb->is_directory) {
                file_to_cat = dest_fcb;
                token = strtok(NULL,"/");
            }else{
                if (strtok(NULL,"/") != NULL){ //trying to access a file as if it was a directory
                    printf("cat: %s: File o directory non esistente\n", token);
                    executing_command->return_value = FILE_NOT_FOUND;
                }break;
            }
        }
    }
    if (dest_fcb->is_directory){
        printf("cat: %s: È una directory\n", dest_fcb->filename);
        executing_command->return_value = ERR_FILE_IS_A_DIR;
        return;
           
    }
    //everything ok: read the file and print the result 
    char* dest = (char*)malloc(dest_fcb->size);
    vrFS_readFile(disk_layout, dest_fcb, dest);
    dest = dest + 136;
    printf("%s\n", dest);
    executing_command->return_value = SUCCESS;    
}