#include "vrSHELL_commands.h"
#include "../vrFS/vrFS.h"
#include <stdio.h>


void vr_import(){
    char* filename = (char*)executing_command->command_args[0];
    int fd = open(filename, O_RDONLY); //open in read-only
    if (fd < 0) {
        printf("import: %s: file non esistente\n", filename);
        executing_command->return_value = ERR_IMPORT;
        return;
    }
    struct stat st;
    if (fstat(fd, &st) == -1) {
        executing_command->return_value = ERR_IMPORT;
        return;
    }
    
    int file_size = st.st_size;

    char* buffer = (char*) mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fd, 0);

    command_wrapper(SHELL_TOUCH, filename);
    command_wrapper(SHELL_APPEND, filename, buffer);
    executing_command->return_value = SUCCESS;
     

}