#include "vrSHELL_commands.h"
#include "../vrFS/vrFS.h"
#include <stdio.h>

void vr_export(){
    char* filename = (char*)executing_command->command_args[0];
    int fd = open(filename, O_RDWR|O_CREAT, 0660);
    if (fd == -1){
        executing_command->return_value = ERR_EXPORT;
        return;
    }

    
    FCB* file_to_cat;
    file_to_cat = currentFCB;
    int fcb_index = vrFS_dir_search(disk_layout, file_to_cat->first_index, filename);
    if (fcb_index == FILE_NOT_FOUND){
        printf("export: %s: File o directory non esistente\n",filename);
        executing_command->return_value = ERR_FILE_NOT_FOUND;
        return;
    }
    FCB * dest_fcb = (FCB*) goto_memoryarea(disk_layout, fcb_index);
    
    if (dest_fcb->is_directory){
        printf("export: %s: È una directory\n", dest_fcb->filename);
        executing_command->return_value = ERR_FILE_IS_A_DIR;
        return;
           
    }
    if (dest_fcb->size > sizeof(FCB)){
        char* src = (char*)malloc(dest_fcb->size+1);
        vrFS_readFile(disk_layout, dest_fcb, src);
        src[dest_fcb->size] = '\0';
        src = src + sizeof(FCB);
        //ora ho dest con contenuto del file 
        int file_size = strlen(src);
        ftruncate(fd, file_size);
        char* dest_file = (char*)mmap(NULL, file_size, PROT_WRITE|PROT_READ, MAP_SHARED, fd, 0);
        memcpy(dest_file, src, file_size);
    
    }

    
    executing_command->return_value = SUCCESS;        

}