#include "vrSHELL_commands.h"
#include "../vrFS/vrFS.h"
#include <stdio.h>


void vr_cat(){
    char* filename = (char*)malloc(MAX_FILENAME_LENGTH+1);
    
    FCB* file_to_cat;
    file_to_cat = currentFCB;

    strcpy(filename, (char*)executing_command->command_args[0]);

    char* token = strtok(filename,"/");
    FCB dest_fcb;
    while(token != NULL){
        printf("token %s\n", token);
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
                *parent = *(file_to_cat->directory);
                file_to_cat = parent;
                token = strtok(NULL,"/");
                continue;
            }
        }else {
            int x = vrFS_dir_search(disk_layout, file_to_cat, &dest_fcb, token);
            if (x == FILE_NOT_FOUND){
                printf("cat: %s: File o directory non esistente\n",token);
                executing_command->return_value = ERR_FILE_NOT_FOUND;
                return;
            }
            if (dest_fcb.is_directory) file_to_cat = &dest_fcb;
            token = strtok(NULL,"/");

            
        }

    }
    if (dest_fcb.is_directory){
        printf("cat: %s: È una directory\n", dest_fcb.filename);
        executing_command->return_value = ERR_FILE_IS_A_DIR;
        return;
           
    }
    char* dest = (char*)malloc(dest_fcb.size);
    vrFS_readFile(disk_layout, &dest_fcb, dest);
    printf("%s\n", dest);
    executing_command->return_value = SUCCESS;
    

    
}