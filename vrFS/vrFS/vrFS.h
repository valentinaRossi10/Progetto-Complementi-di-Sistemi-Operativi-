#pragma once
#include "vrFS_disk.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <assert.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>



void vrFS_format_block(DiskLayout* disk_layout, Disk block);
void vrFS_format_disk(DiskLayout* disk_layout);
int vrFS_load_file(DiskLayout* disk_layout, FCB* fcb);
void vrFS_remove_file(DiskLayout* disk_layout, FCB* fcb);
Disk vrFS_MemoryBlock_byFatIndex(DiskLayout* disk_layout, int index);
int vrFS_BlockIndex_byBlock(DiskLayout* disk_layout, Disk block);
int vrFS_FATValue_byMemoryBlock(DiskLayout* disk_layout, Disk block);
FreeTableFlags vrFS_FreeTableValue_byMemoryBlock(DiskLayout* disk_layout, Disk block);
int vrFS_first_free_block_index(DiskLayout* disk_layout);
int vrFS_writeFile(DiskLayout* disk_layout, FCB* fcb, char* buffer, int buffer_size);
int vrFS_readFile(DiskLayout* disk_layout, FCB* fcb, char* dest);
