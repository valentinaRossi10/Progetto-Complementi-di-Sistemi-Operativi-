#include "vrFS_disk.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <assert.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>
 
int fd; 
void disk_init(DiskLayout* disk_layout){ //remember to alloc memory 
    fd = open("./diskFile", O_RDWR|O_CREAT, 0660); 
    assert(fd > 0 && "open failed");

    off_t disk_dimension = DISK_SIZE;
    int ret = ftruncate(fd, disk_dimension);
    assert(ret != -1 && "ftruncate failed");

    // the flag MAP_SHARED allows us to do side effect on the disk
    // to flush our changes to the persistent memory we combine it with msync
    // as mmap documentation suggests

    disk_layout->disk = (Disk)mmap(NULL, disk_dimension, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    disk_layout->fat = (int*)disk_layout->disk; 
    disk_layout->free_table = (int*)(disk_layout->disk + FAT_SIZE); 
    disk_layout->start_of_files = disk_layout->disk + 2 * FAT_SIZE;
    
    //initializing FAT

    for (int i = 0; i < MAX_NUM_BLOCK -1; i++){
        disk_layout->fat[i] = i+1;
    }
    disk_layout->fat[MAX_NUM_BLOCK-1] = -1;

    //initializing free_table 

    for (int i = 0; i < MAX_NUM_BLOCK; i++){
        disk_layout->free_table[i] = Free_Block;
    }


}

void disk_shutdown(DiskLayout* disk_layout){
    disk_layout->fat = NULL;
    disk_layout->free_table = NULL;
    int ret = munmap(disk_layout->disk, DISK_SIZE);    
    assert (ret > 0 && "munmap failed");
    disk_layout->disk = NULL;
    ret = close(disk_layout->fd);
    assert (ret > 0 && "close failed");
}

Disk disk_MemoryBlock_byFatIndex(int index, DiskLayout* disk_layout){
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
    int index = BlockIndex_byBlock(disk_layout, block);
    return disk_layout->fat[index];
}

FreeTableFlags disk_FreeTableValue_byMemoryBlock(DiskLayout* disk_layout, Disk block){
    //it returns Free_block if the block is free, Taken_block otherwise
    int index = BlockIndex_byBlock(disk_layout, block);
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
int disk_remove_file(DiskLayout* disk_layout, FCB* fcb){
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

int disk_write_block(DiskLayout* disk_layout, void* buffer, int size, int index, int block_offset){
    ///write size bytes on disk block at position index. If offset != 0 (to handle append operations) start from named offset in the block 
    assert(index >= 0 && index < MAX_NUM_BLOCK && 'invalid index');
    assert(size <= BLOCK_SIZE);
    assert(block_offset >= 0 && 'invalid offset');
    if (block_offset  > 0){
        assert(size <= BLOCK_SIZE-block_offset);
    }
    int bytes_to_write = size;
    if (lseek(fd, 2*FAT_SIZE + index*BLOCK_SIZE + block_offset, SEEK_SET) <  0) return -1; // move fd offset to this block
    if (write(fd, buffer, bytes_to_write) != bytes_to_write) return -1; 
    return 1;
}

char* disk_read_block(DiskLayout* disk_layout, int size, int index);



int main(){
    printf("***********************TESTING DISK**************************\n");
    DiskLayout disk;
    disk_init(&disk);

    printf("\n*********BLOCK AT POSITION 0********* \n");
    Disk block = disk_MemoryBlock_byFatIndex(0, &disk); 
    int difference = block-disk.start_of_files;
    printf("difference (should be 0) : %d\n",difference);
    int index = disk_BlockIndex_byBlock(&disk, block);
    printf("index (should be 0) : %d\n", index);
    int fat_val = disk_FATValue_byMemoryBlock(&disk, block);
    printf("fat_val (should be 1) : %d\n", fat_val);
    FreeTableFlags free_val = disk_FreeTableValue_byMemoryBlock(&disk, block);
    printf("free_val (should be FreeBlock (1)) : %d\n",free_val);
    
    printf("\n*********BLOCK AT POSITION 100********* \n");
    Disk block2 = disk_MemoryBlock_byFatIndex(100, &disk); 
    difference = block2-disk.start_of_files;
    printf("difference (should be 100*4000) : %d\n",difference);
    index = disk_BlockIndex_byBlock(&disk, block2);
    printf("index (should be 100) : %d\n", index);
    fat_val = disk_FATValue_byMemoryBlock(&disk, block2);
    printf("fat_val (should be 101) : %d\n", fat_val);
    free_val = disk_FreeTableValue_byMemoryBlock(&disk, block2);
    printf("free_val (should be FreeBlock (1)) : %d\n",free_val);
   
}