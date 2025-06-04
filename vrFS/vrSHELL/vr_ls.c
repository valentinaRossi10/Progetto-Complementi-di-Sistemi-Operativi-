#include "vrSHELL_commands.h"
#include "../vrFS/vrFS.h"

void vr_ls(){

    char* filename = (char*)malloc(MAX_FILENAME_LENGTH);
    FCB* fcb_to_list;
    fcb_to_list = currentFCB;
    if (executing_command->command_number == SHELL_LS_WITH_ARG){ 
        //devo fare listing di una target directory 
        strcpy(filename,  (char*)executing_command->command_args[0]);
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
                    *parent = *(fcb_to_list->directory);
                    fcb_to_list = parent;
                    token = strtok(NULL,"/");
                    continue;
                }
            }else {
                int x = vrFS_dir_search(disk_layout, fcb_to_list, &dest_fcb, token);
                if (x == FILE_NOT_FOUND){
                    printf("ls: %s: File o directory non esistente\n",token);
                    executing_command->return_value = ERR_FILE_NOT_FOUND;
                    return;
                }
                if (!dest_fcb.is_directory){
                    printf("ls: %s: Non è una directory", dest_fcb.filename);
                    executing_command->return_value = ERR_FILE_NOT_A_DIR;
                    return;
                }
                FCB* new_fcb = (FCB*)malloc(sizeof(FCB));
                *new_fcb = dest_fcb;
                new_fcb->directory = fcb_to_list;  // set parent
                fcb_to_list = new_fcb;  
                
                token = strtok(NULL,"/");
            }
        }
    }

    int num_files = fcb_to_list->size / sizeof(FCB);
    char* dest = (char*)malloc(fcb_to_list->size);
    int ret = vrFS_readFile(disk_layout, fcb_to_list, dest);
    assert(ret == SUCCESS && "read error");
    FCB* fcb_array = (FCB*)dest;
    FCB* aux;
    for (int i = 0; i < num_files; i++){
        aux = fcb_array+i;
        printf("%s\n",aux->filename);
        
    }
    executing_command->return_value = SUCCESS;


}

