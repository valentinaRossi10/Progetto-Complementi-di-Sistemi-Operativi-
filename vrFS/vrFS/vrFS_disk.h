#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <assert.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "vrFS_constants.h"

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
Disk MemoryBlock_byFatIndex(int index, DiskLayout* disk_layout);
int BlockIndex_byBlock(DiskLayout* disk_layout, Disk block);
int FATValue_byMemoryBlock(DiskLayout* disk_layout, Disk block);
FreeTableFlags FreeTableValue_byMemoryBlock(DiskLayout* disk_layout, Disk block);
