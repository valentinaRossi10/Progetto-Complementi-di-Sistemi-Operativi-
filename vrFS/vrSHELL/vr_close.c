#include "vrSHELL_commands.h"
#include "../vrFS/vrFS.h"
#include <stdio.h>


void vr_close(){
    //disk_shutdown(disk_layout);
    FCB* try = (FCB*)(disk_layout->start_of_files);
    FCB_print(disk_layout, try);
    try = (FCB*)(disk_layout->start_of_files+BLOCK_SIZE);
    FCB_print( disk_layout,try);
    
    // siccome la fcb non 
    msync(disk_layout->disk, DISK_SIZE, MS_SYNC);
    munmap(disk_layout->disk, DISK_SIZE);
    close(disk_layout->fd);
    printf("disk closed\n");
    
}