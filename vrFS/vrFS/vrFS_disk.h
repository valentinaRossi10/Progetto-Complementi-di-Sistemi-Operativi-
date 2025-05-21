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
void disk_format_block(DiskLayout* disk_layout, Disk block);
int disk_load_file(DiskLayout* disk_layout, FCB* fcb);
int disk_remove_file(DiskLayout* disk_layout, FCB* fcb);
int disk_write(DiskLayout* disk_layout, void* content, int size, int index);
char* disk_read(DiskLayout* disk_layout, int size, int index);


Disk disk_MemoryBlock_byFatIndex(int index, DiskLayout* disk_layout);
int disk_BlockIndex_byBlock(DiskLayout* disk_layout, Disk block);
int disk_FATValue_byMemoryBlock(DiskLayout* disk_layout, Disk block);
FreeTableFlags disk_FreeTableValue_byMemoryBlock(DiskLayout* disk_layout, Disk block);
int disk_first_free_block_index(DiskLayout* disk_layout);
