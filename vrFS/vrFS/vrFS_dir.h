#pragma once
#include "vrFS_disk.h"
#include "vrFS_block_manager.h"
#include "vrFS.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <assert.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>



void vrFS_update_fcb_in_dir(DiskLayout* disk_layout, FCB* updated_fcb);
void vrFS_remove_fcb_from_dir(DiskLayout* disk_layout, FCB* fcb_to_remove);
int vrFS_dir_search(DiskLayout* disk_layout, FCB* fcb_dir, FCB* returned_fcb, char* filename);