#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <assert.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "vrFS_constants.h"
#include "fcb.h"

typedef char* Disk;
typedef int* FAT;
typedef int* FreeBlocksTable;

typedef enum{
    Free_Block = 1, 
    Taken_Block = 0
}FreeTableFlags;

//useful data structure to keep track of the disk 
typedef struct DiskLayout{
    int fd; // useful for shutdown
    Disk disk;
    FAT fat;
    FreeBlocksTable free_table;
    Disk start_of_files; // free_table contains all block with corresponding flag  
}DiskLayout;

void disk_init();
void disk_shutdown();
int disk_write_block(DiskLayout* disk_layout, void* buffer, int size, int index, int block_offset);
char* disk_read_block(DiskLayout* disk_layout, int size, int index);


