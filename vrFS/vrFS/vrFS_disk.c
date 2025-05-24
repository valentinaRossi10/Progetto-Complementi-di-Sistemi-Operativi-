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

    for (int i = 0; i < MAX_NUM_BLOCK; i++){
        disk_layout->fat[i] = -1;
    }

    //initializing free_table 

    for (int i = 0; i < MAX_NUM_BLOCK; i++){
        disk_layout->free_table[i] = Free_Block;
    }


}

void disk_shutdown(DiskLayout* disk_layout){
    printf("shutdown...\n");
    disk_layout->fat = NULL;
    disk_layout->free_table = NULL;
    int ret = munmap(disk_layout->disk, DISK_SIZE);    
    assert (ret == 0 && "munmap failed");
    disk_layout->disk = NULL;
    ret = close(fd);
    assert (ret == 0 && "close failed");
    printf("shutdown completed\n");
}


int disk_write_block(DiskLayout* disk_layout, void* buffer, int size, int index, int block_offset){
    ///write size bytes on disk block at position index. If offset != 0 (to handle append operations) start from named offset in the block 
    assert(index >= 0 && index < MAX_NUM_BLOCK && "invalid index");
    assert(size <= BLOCK_SIZE);
    assert(block_offset >= 0 && "invalid offset");
    if (block_offset  > 0){
        assert(size <= BLOCK_SIZE-block_offset);
    }
    int bytes_to_write = size;
    if (lseek(fd, 2*FAT_SIZE + index*BLOCK_SIZE + block_offset, SEEK_SET) <  0) return WRITE_ERROR; // move fd offset to this block
    if (write(fd, buffer, bytes_to_write) != bytes_to_write) return WRITE_ERROR; 
    return bytes_to_write;
}

int disk_read_block(DiskLayout* disk_layout, char* buffer, int size, int index){
    assert(index >= 0 && index < MAX_NUM_BLOCK && "invalid index");
    if (lseek(fd, 2*FAT_SIZE + index*BLOCK_SIZE, SEEK_SET) <  0) return READ_ERROR; // move fd offset to this block
    if (read(fd, buffer,size) != size) return READ_ERROR; 
    return size;

}



