#include "vrSHELL_commands.h"
#include "../vrFS/vrFS.h"
#include <stdio.h>


void vr_close(){
    //disk_shutdown(disk_layout);
    
    // siccome la fcb non 
    msync(disk_layout->disk, DISK_SIZE, MS_SYNC);
    munmap(disk_layout->disk, DISK_SIZE);
    close(disk_layout->fd);
    printf("disk closed\n");
    
}