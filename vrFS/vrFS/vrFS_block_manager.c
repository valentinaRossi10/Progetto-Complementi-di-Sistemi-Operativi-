#include "vrFS_block_manager.h"

Disk vrFS_MemoryBlock_byFatIndex(DiskLayout* disk_layout, int index){
    /// it returns the position of the block of number index from the start of the disk
    assert(index < MAX_NUM_BLOCK && "invalid index");
    return disk_layout->start_of_files + (index*BLOCK_SIZE);
}

int vrFS_BlockIndex_byBlock(DiskLayout* disk_layout, Disk block){
    ///given a block it returns its index 
    off_t offset = (block - disk_layout->start_of_files)/BLOCK_SIZE;
    assert(offset >= 0 && offset < MAX_NUM_BLOCK && "invalid_offset");
    return offset;
}

int vrFS_FATValue_byMemoryBlock(DiskLayout* disk_layout, Disk block){
    //given the memory block it returns the index of the next block 
    int index = vrFS_BlockIndex_byBlock(disk_layout, block);
    return disk_layout->fat[index];
}

FreeTableFlags vrFS_FreeTableValue_byMemoryBlock(DiskLayout* disk_layout, Disk block){
    //it returns Free_block if the block is free, Taken_block otherwise
    int index = vrFS_BlockIndex_byBlock(disk_layout, block);
    return disk_layout->free_table[index];
}

int vrFS_first_free_block_index(DiskLayout* disk_layout){
    //it returns the index of the first free block 
    for (int i = 0; i < MAX_NUM_BLOCK; i++){
        if (disk_layout->free_table[i] == Free_Block){
            return i;
        }
    }
    return NO_FREE_BLOCKS;
}

void vrFS_format_block(DiskLayout* disk_layout, Disk block){
    memset(block, 0, BLOCK_SIZE);
} 

void vrFS_format_disk(DiskLayout* disk_layout){
    for (int i = 0; i < MAX_NUM_BLOCK; i++){
        Disk block = vrFS_MemoryBlock_byFatIndex(disk_layout, i);
        vrFS_format_block(disk_layout, block);
    }
}