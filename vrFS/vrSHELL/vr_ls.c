#include "vrSHELL_commands.h"
#include "../vrFS/vrFS.h"

void vr_ls(){

    char* filename = (char*)malloc(MAX_FILENAME_LENGTH);
    FCB* fcb_to_list;
    fcb_to_list = currentFCB;
   
    if (executing_command->command_number == SHELL_LS_WITH_ARG){ 
        // need to list a target directory 
        strcpy(filename, (char*)executing_command->command_args[0]);
        char* token = strtok(filename,"/");
        FCB* dest;

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
                    fcb_to_list = (FCB*)goto_memoryarea(disk_layout, fcb_to_list->directory);
                    token = strtok(NULL,"/");
                
                    continue;
                }
            }else {
                int fcb_index = vrFS_dir_search(disk_layout, fcb_to_list->first_index, token);
                if (fcb_index == FILE_NOT_FOUND){
                    printf("ls: %s: File o directory non esistente\n",token);
                    executing_command->return_value = ERR_FILE_NOT_FOUND;
                    return;
                }
                dest = (FCB*)goto_memoryarea(disk_layout, fcb_index);

                if (!dest->is_directory){
                    printf("ls: %s: Non è una directory", dest->filename);
                    executing_command->return_value = ERR_FILE_NOT_A_DIR;
                    return;
                }
                fcb_to_list = dest;  
                
                token = strtok(NULL,"/");
            }
        }
    }

    int num_files = (fcb_to_list->size -sizeof(FCB))/ sizeof(int);
    if (num_files == 0){ //empty folder
        executing_command->return_value = SUCCESS;
        return;
    }
    //read the content of the directory 
    char* dest_buf = (char*)malloc(fcb_to_list->size + sizeof(FCB)); //
    int ret = vrFS_readFile(disk_layout, fcb_to_list, dest_buf);
    dest_buf = dest_buf+sizeof(FCB);
    assert(ret == SUCCESS && "read error");
    
    //cast it to a fcb array 
    int* array = (int*)dest_buf;
    FCB aux;
    
    //scan the array
    for (int i = 0; i < num_files; i++){
        getFCB_by_block(disk_layout, array[i], &aux); // safe to use this here cause we only print the name 
        printf("%s\n",aux.filename);
        
    }
    executing_command->return_value = SUCCESS;


}

