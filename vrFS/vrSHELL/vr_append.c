#include "vrSHELL_commands.h"
#include "../vrFS/vrFS.h"
#include <stdio.h>
#include <string.h>


void vr_append(){
    char* filename = (char*)malloc(MAX_FILENAME_LENGTH+1);
    strcpy(filename, (char*)executing_command->command_args[0]);

    char* text = (char*)executing_command->command_args[1]; // text to append
    FCB* aux_dir; // auxiliary variable to explore directories 
    aux_dir = currentFCB;

    char* token = strtok(filename,"/");
    FCB dest_fcb;

    while(token != NULL){
        //parse the path 

        if (strcmp(".", token) == 0) { // aux_dir stays the same
            token = strtok(NULL, "/");
            continue;
        }
        else if (strcmp("..", token) == 0) { // aux_dir becomes aux_dir's parent
            if (currentFCB->directory == NULL) {
                // if you are in the root directory and execute cd ..
                // it does not raise any error, it simply stays there
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
            // we find for the right fcb in the disk 
            if (x == FILE_NOT_FOUND){
                printf("rm: %s: File o directory non esistente\n",token);
                executing_command->return_value = ERR_FILE_NOT_FOUND;
                return;
            }
            if (dest_fcb.is_directory){ //if it is a directory, we keep parsing the path
                aux_dir = &dest_fcb;
                token = strtok(NULL,"/");
                continue;
            }else{ // if it's not a directory AND it is not the last token ERROR
                if (strtok(NULL,"/") != NULL){ //trying to access a file as if it was a directory
                    printf("append: %s: File o directory non esistente\n", token);
                    executing_command->return_value = ERR_FILE_NOT_FOUND;
                    return;
                }
                break;
            }
        }
    }
    if(dest_fcb.is_directory){ // at the end of parsing if the last token is a directory : ERROR 
        printf("append: %s: È una directory\n", dest_fcb.filename);
        executing_command->return_value = ERR_FILE_IS_A_DIR;
        return;
    }
    
    // everything went ok: we write the text in the file
    int x = vrFS_writeFile(disk_layout, &dest_fcb, text, strlen(text));
    if (x == SUCCESS) executing_command->return_value = SUCCESS;
    else executing_command->return_value = WRITE_ERROR;
}



