#include "vrSHELL_commands.h"
#include "../vrFS/vrFS.h"
#include <stdio.h>


void vr_close(){
    disk_shutdown(disk_layout);
    printf("disk closed\n");
}