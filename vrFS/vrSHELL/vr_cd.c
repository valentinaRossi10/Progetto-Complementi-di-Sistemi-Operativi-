#include "vrSHELL_commands.h"
#include "../vrFS/vrFS.h"
#include <stdio.h>

void vr_cd(){
    char* filename = (char*)executing_command->command_args[0];



    FCB dest_fcb;
    int x = vrFS_dir_search(disk_layout, currentFCB, &dest_fcb, filename);
    if (x == FILE_NOT_FOUND){
        printf("%s : File o directory non esistente\n",filename);
        executing_command->return_value = CD_ERR_FILE_NOT_FOUND;
        return;
    }
    if (!dest_fcb.is_directory){
        printf("%s : Non è una directory", dest_fcb.filename);
        executing_command->return_value = CD_ERR_FILE_NOT_A_DIR;
        return;
    }
    *currentFCB = dest_fcb;


}