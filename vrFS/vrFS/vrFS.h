#pragma once
#include "vrFS_disk.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <assert.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>



void disk_format_block(DiskLayout* disk_layout, Disk block);
int disk_load_file(DiskLayout* disk_layout, FCB* fcb);
void disk_remove_file(DiskLayout* disk_layout, FCB* fcb);


Disk disk_MemoryBlock_byFatIndex(DiskLayout* disk_layout, int index);
int disk_BlockIndex_byBlock(DiskLayout* disk_layout, Disk block);
int disk_FATValue_byMemoryBlock(DiskLayout* disk_layout, Disk block);
FreeTableFlags disk_FreeTableValue_byMemoryBlock(DiskLayout* disk_layout, Disk block);
int disk_first_free_block_index(DiskLayout* disk_layout);



