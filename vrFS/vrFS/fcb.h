#pragma once
#include <assert.h>
#include <stdio.h>
#include "vrFS_constants.h"
#include "vrFS_disk.h"

typedef struct FCB{
    char filename[MAX_FILENAME_LENGTH];
    int first_index;
    int last_index;
    //struct FCB* directory;
    int directory; // now its an int
    int size;
    char* ownership;
    int is_directory; // boolean value, 1 means it is a directory 0 means it is a regular file  
}FCB;


void FCB_init(FCB* fcb);
void FCB_print(DiskLayout* disk_layout, FCB* fcb);
void FCB_deepcopy(FCB* src, FCB* dest);
void getFCB_by_block(DiskLayout* disk_layout,int block, FCB* fcb);
char* goto_memoryarea(DiskLayout* disk_layout, int block);