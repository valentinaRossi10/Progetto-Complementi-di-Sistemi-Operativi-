#pragma once
#include "vrFS_disk.h"
#include "vrFS_block_manager.h"
#include "vrFS_dir.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <assert.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>



int vrFS_load_file(DiskLayout* disk_layout, FCB* fcb);
int vrFS_remove_file(DiskLayout* disk_layout, FCB* fcb);
int vrFS_writeFile(DiskLayout* disk_layout, FCB* fcb, char* buffer, int buffer_size);
int vrFS_readFile(DiskLayout* disk_layout, FCB* fcb, char* dest);
