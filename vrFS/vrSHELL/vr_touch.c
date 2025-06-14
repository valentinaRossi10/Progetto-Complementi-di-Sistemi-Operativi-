#include "vrSHELL_commands.h"
#include "../vrFS/vrFS.h"
#include <stdio.h>
#include <string.h>


void vr_touch(){
    char* filename = (char*)malloc(MAX_FILENAME_LENGTH+1);
    
    FCB* aux_dir;
    aux_dir = currentFCB;
    strcpy(filename, (char*)executing_command->command_args[0]);

    char* token = strtok(filename,"/");
    FCB dest_fcb;

    while(token != NULL){
        if (strcmp(".", token) == 0) {
            token = strtok(NULL, "/");
            continue;
        }
        else if (strcmp("..", token) == 0) {
            if (aux_dir->directory == NULL) {
                token = strtok(NULL,"/");
                continue;
            }else{
                aux_dir = aux_dir->directory;
                token = strtok(NULL,"/");
                continue;
            }
        }else {
            int x = vrFS_dir_search(disk_layout, aux_dir, &dest_fcb, token);
            if (x == FILE_NOT_FOUND){
                if (strtok(NULL,"/") == NULL){ // here we are, we need to create the file
                    FCB new_file;
                    FCB_init(&new_file);
                    new_file.directory = aux_dir;

                    new_file.filename = (char*)malloc(strlen(token)+1);
                    strcpy(new_file.filename, token);

                    new_file.is_directory = 0;
                    new_file.ownership = aux_dir->ownership;
                    int x = vrFS_load_file(disk_layout, &new_file);

                    if (x == NO_FREE_BLOCKS) {
                        executing_command->return_value = NO_FREE_BLOCKS;
                        printf("touch: Memoria piena\n");
                        return;
                    }
                    executing_command->return_value = SUCCESS;
                    return;

                }
                else{ //there is a mistake: trying to access to a non-existing directory  
                    printf("touch: %s: File o directory non esistente\n",token);
                    executing_command->return_value = ERR_FILE_NOT_FOUND;
                    return;
                }
            }
            if (dest_fcb.is_directory) {
                FCB* next_dir = (FCB*)malloc(sizeof(FCB));
                *next_dir = dest_fcb;
                aux_dir = next_dir;
                token = strtok(NULL,"/");
            }
        }
    }

}