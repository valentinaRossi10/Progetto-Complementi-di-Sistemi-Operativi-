#include "vrFS.h"
#include <string.h>

Disk disk_MemoryBlock_byFatIndex(DiskLayout* disk_layout, int index){
    /// it returns the position of the block of number index from the start of the disk
    assert(index*BLOCK_SIZE < DISK_SIZE && "invalid index");
    return disk_layout->start_of_files + (index*BLOCK_SIZE);
}

int disk_BlockIndex_byBlock(DiskLayout* disk_layout, Disk block){
    ///given a block it returns its index 
    off_t offset = (block - disk_layout->start_of_files)/BLOCK_SIZE;
    assert(offset >= 0 && offset < MAX_NUM_BLOCK && "invalid_offset");
    return offset;
}

int disk_FATValue_byMemoryBlock(DiskLayout* disk_layout, Disk block){
    //given the memory block it returns the index of the next block 
    int index = disk_BlockIndex_byBlock(disk_layout, block);
    return disk_layout->fat[index];
}

FreeTableFlags disk_FreeTableValue_byMemoryBlock(DiskLayout* disk_layout, Disk block){
    //it returns Free_block if the block is free, Taken_block otherwise
    int index = disk_BlockIndex_byBlock(disk_layout, block);
    return disk_layout->free_table[index];
}

int disk_first_free_block_index(DiskLayout* disk_layout){
    //it returns the index of the first free block 
    for (int i = 0; i < MAX_NUM_BLOCK; i++){
        if (disk_layout->free_table[i] == Free_Block){
            return i;
        }
    }
    return NO_FREE_BLOCKS;
}

void disk_format_block(DiskLayout* disk_layout, Disk block){
    memset(block, 0, BLOCK_SIZE);
} 

int disk_load_file(DiskLayout* disk_layout, FCB* fcb){
    ///initializes the first index of the file (last index = first index for the moment, we will update it later with write function)
    fcb->first_index = disk_first_free_block_index(disk_layout);
    disk_layout->free_table[fcb->first_index] = Taken_Block;    
    fcb->last_index = fcb->first_index;
    // fat val is already -1 
    return fcb->first_index;

}
void disk_remove_file(DiskLayout* disk_layout, FCB* fcb){
    ///frees the blocks occupied by the file and formats them 
    int i = fcb->first_index;
    while(disk_layout->fat[i]!= -1){
        Disk block = disk_MemoryBlock_byFatIndex(disk_layout, i);
        disk_format_block(disk_layout, block);
        disk_layout->fat[i] = -1;
        assert(disk_layout->free_table[i] == Taken_Block && "block already free");
        disk_layout->free_table[i] = Free_Block;
        i++;
    }
}


