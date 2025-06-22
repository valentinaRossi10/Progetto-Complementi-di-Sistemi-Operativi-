#include "vrSHELL_commands.h"
#include "../vrFS/vrFS.h"
#include <stdio.h>


void vr_format(){
    char* filename = (char*)malloc(MAX_FILENAME_LENGTH);
    strcpy(filename,(char*)executing_command->command_args[0]);

    int size = atoi((char*)executing_command->command_args[1]);
    int ret = disk_init(disk_layout, size, filename);


    vrFS_format_disk(disk_layout);
    
    if (ret == DISK_INIT_ERROR){ 
        printf("format: la dimensione specificata eccede il limite massimo consentito (%d blocchi).\n", MAX_ALLOWED_BLOCKS);
        executing_command->return_value = ERR_FORMAT;
        return;
    }

    printf("format : done\n");

    //create root directory  
    FCB root;
    FCB_init(&root);
    root.directory = -1;
    strcpy(root.filename, "root");
    root.is_directory = 1;
    root.ownership = getenv("LOGNAME");

    //load on disk 
    vrFS_load_file(disk_layout, &root);

    currentFCB = (FCB*)(disk_layout->start_of_files + root.first_index * BLOCK_SIZE);

   
    executing_command->return_value = SUCCESS;

}