#include "vrSHELL_commands.h"
#include "../vrFS/vrFS.h"
#include <stdio.h>


void vr_cat(){
    char* filename = (char*)executing_command->command_args[0];
    FCB file_to_cat;
    int x = vrFS_dir_search(disk_layout, currentFCB,&file_to_cat, filename);
    if (x == FILE_NOT_FOUND) {
        executing_command->return_value = ERR_FILE_NOT_FOUND;
        printf("cat: %s: File o directory non esistente\n", filename);
        return;
    }
    if (file_to_cat.is_directory) {
        executing_command->return_value = ERR_FILE_IS_A_DIR;
        printf("cat: %s: È una directory\n", file_to_cat.filename);
        return;

    }
    char* dest = (char*)malloc(file_to_cat.size);
    vrFS_readFile(disk_layout, &file_to_cat, dest);
    printf("%s\n", dest);
    executing_command->return_value = SUCCESS;
}