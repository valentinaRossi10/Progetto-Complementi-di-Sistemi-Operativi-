#include "vrFS_block_manager.h"

/*FUNCTIONS TO MANAGE BLOCKS, FAT TABLE AND FREE TABLE*/

Disk vrFS_MemoryBlock_byFatIndex(DiskLayout* disk_layout, int index){
    // it returns the address of the block of number index from the start of the disk
    assert(index < MAX_NUM_BLOCK && "invalid index");
    return disk_layout->start_of_files + (index*BLOCK_SIZE);
}


int vrFS_BlockIndex_byBlock(DiskLayout* disk_layout, Disk block){
    //given a block, it returns its index 
    off_t offset = (block - disk_layout->start_of_files)/BLOCK_SIZE;
    assert(offset >= 0 && offset < MAX_NUM_BLOCK && "invalid_offset");
    return offset;
}


int vrFS_first_free_block_index(DiskLayout* disk_layout){
    //it returns the index of the first free block 
    //it scans the free_table until it finds a free block 
    for (int i = 0; i < MAX_NUM_BLOCK; i++){
        if (disk_layout->free_table[i] == Free_Block){
            return i;
        }
    }
    return NO_FREE_BLOCKS;
}


void vrFS_format_block(DiskLayout* disk_layout, Disk block){
    //formats a block setting all its bits to 0 
    memset(block, 0, BLOCK_SIZE);
} 


void vrFS_format_disk(DiskLayout* disk_layout){
    //it formats all the blocks of the disk 
    for (int i = 0; i < MAX_NUM_BLOCK; i++){
        Disk block = vrFS_MemoryBlock_byFatIndex(disk_layout, i);
        vrFS_format_block(disk_layout, block);
    }
}