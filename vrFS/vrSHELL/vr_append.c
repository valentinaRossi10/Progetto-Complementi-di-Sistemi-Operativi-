#include "vrSHELL_commands.h"
#include "../vrFS/vrFS.h"
#include <stdio.h>
#include <string.h>


void vr_append(){
    char* filename = (char*)malloc(MAX_FILENAME_LENGTH+1);
    strcpy(filename, (char*)executing_command->command_args[0]);

    char* text = (char*)executing_command->command_args[1];
    FCB* aux_dir;
    aux_dir = currentFCB;

    char* token = strtok(filename,"/");
    FCB dest_fcb;

    while(token != NULL){
        if (strcmp(".", token) == 0) {
            token = strtok(NULL, "/");
            continue;
        }
        else if (strcmp("..", token) == 0) {
            if (currentFCB->directory == NULL) {
                token = strtok(NULL,"/");
                continue;
            }else{
                FCB* parent = (FCB*)malloc(sizeof(FCB));
                *parent = *(aux_dir->directory);
                aux_dir = parent;
                token = strtok(NULL,"/");
                continue;
            }
        }else {
            int x = vrFS_dir_search(disk_layout, aux_dir, &dest_fcb, token);
            if (x == FILE_NOT_FOUND){
                printf("rm: %s: File o directory non esistente\n",token);
                executing_command->return_value = ERR_FILE_NOT_FOUND;
                return;
            }
            if (dest_fcb.is_directory){
                aux_dir = &dest_fcb;
                token = strtok(NULL,"/");
                continue;
            }else{
                if (strtok(NULL,"/") != NULL){ //trying to access a file as if it was a directory
                    printf("append: %s: File o directory non esistente\n", token);
                    executing_command->return_value = ERR_FILE_NOT_FOUND;
                    return;
                }
                break;
            }
        }
    }
    if(dest_fcb.is_directory){
        printf("append: %s: È una directory\n", dest_fcb.filename);
        executing_command->return_value = ERR_FILE_IS_A_DIR;
        return;
    }
    int x = vrFS_writeFile(disk_layout, &dest_fcb, text, strlen(text));
    if (x == SUCCESS) executing_command->return_value = SUCCESS;
    else executing_command->return_value = WRITE_ERROR;
}



