#include "vrSHELL_commands.h"
#include "../vrFS/vrFS.h"
#include <stdio.h>


void vr_format(){
    char* filename = (char*)malloc(MAX_FILENAME_LENGTH);
    strcpy(filename,(char*)executing_command->command_args[0]);
    int size = executing_command->command_args[1];
    int ret = disk_init(disk_layout, size, filename);
    if (ret == DISK_INIT_ERROR){ 
        printf("format: la dimensione specificata eccede il limite massimo consentito (%d blocchi).\n", MAX_ALLOWED_BLOCKS);
        executing_command->return_value = ERR_FORMAT;
        return;
    }
    printf("format : done\n");

}