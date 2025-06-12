#include "vrFS.h"
#include <string.h>


int vrFS_load_file(DiskLayout* disk_layout, FCB* fcb){
    ///initializes the first index of the file (last index = first index for the moment, we will update it later with write function)
    int ret = vrFS_first_free_block_index(disk_layout);
    if (ret == NO_FREE_BLOCKS) return NO_FREE_BLOCKS;
    fcb->first_index = ret;
    disk_layout->free_table[fcb->first_index] = Taken_Block;    
    fcb->last_index = fcb->first_index;
    // fat val is already -1
      
    FCB* dir_fcb = fcb->directory;
    if (dir_fcb != NULL){
        vrFS_writeFile(disk_layout, dir_fcb, (char*)fcb, sizeof(FCB));
    }
    return fcb->first_index;
}
 

int vrFS_remove_file(DiskLayout* disk_layout, FCB* fcb){
    ///frees the blocks occupied by the file and formats them 
    if (fcb->is_directory == 1 && fcb->size != 0) {// this means we're trying to remove a directory which is not empty (rmdir only allowed when dir is empty)
        return DIRECTORY_NOT_EMPTY;
    }
    int i = fcb->first_index;
    int next;
    while(disk_layout->fat[i]!= -1){
        next = disk_layout->fat[i];
        Disk block = vrFS_MemoryBlock_byFatIndex(disk_layout, i);
        vrFS_format_block(disk_layout, block);
        disk_layout->fat[i] = -1;
        assert(disk_layout->free_table[i] == Taken_Block && "block already free");
        disk_layout->free_table[i] = Free_Block;
        i = next;
    }
    //update directory 
    vrFS_remove_fcb_from_dir(disk_layout, fcb);
    return SUCCESS;
}




int vrFS_writeFile(DiskLayout* disk_layout, FCB* fcb, char* buffer, int buffer_size){
    int file_size = fcb->size;
    int block_index = fcb->last_index; 
    assert(disk_layout->fat[block_index] == -1 && "not the last block");
    int index_to_write = -1;
    int offset = 0;
    if (file_size%BLOCK_SIZE == 0){
        // it means that the file is alligned with the blocks
        // namely, the file has size 0 (so we start writing from the start of the block) or 
        //the file occupies an amount of space that fits precisely all the blocks till the last one (so we need to start from the next free block)
        if (fcb->first_index != block_index){
            // size != 0, we need to occupy a new block 
            index_to_write = vrFS_first_free_block_index(disk_layout);
            assert(index_to_write != NO_FREE_BLOCKS && "memory full");
            assert(disk_layout->free_table[index_to_write] == Free_Block && "not a free block");
            disk_layout->free_table [index_to_write] = Taken_Block;
            disk_layout->fat[block_index] = index_to_write;  
            disk_layout->fat[index_to_write] = -1;
        }else{
            index_to_write = block_index;
        }
    }else{
        // it means we need to restart writing from a certain offset in the block
        offset = file_size%BLOCK_SIZE;
        index_to_write = block_index;
    }
    int written_bytes = 0;
    int ret, bytes_left, size;
    while(written_bytes < buffer_size){
        //check how many bytes we have to write inside of a block 
        bytes_left = buffer_size-written_bytes;
        if (bytes_left >= BLOCK_SIZE - offset) size = BLOCK_SIZE-offset;
        else size = bytes_left;
        ret = disk_write_block(disk_layout, buffer + written_bytes, size, index_to_write, offset); 
        if (ret != size) return WRITE_ERROR;
        written_bytes+=ret;
        fcb->size += ret;
        //if an entire block has been written, we need to take another free block for our file, update fat and free_list
        if ((offset== 0 && ret == BLOCK_SIZE) || (offset != 0 && ret== BLOCK_SIZE-offset)){
            int new_index_to_write = vrFS_first_free_block_index(disk_layout);
            assert(new_index_to_write != NO_FREE_BLOCKS && "full memory");
            assert(disk_layout->free_table[new_index_to_write] == Free_Block && "not a free block");
            disk_layout->free_table [new_index_to_write] = Taken_Block;
            disk_layout->fat[index_to_write] = new_index_to_write;
            disk_layout->fat[new_index_to_write] = -1;
            fcb->last_index = new_index_to_write;

        } // else we do nothing because if the block is not ended yet we do not need to take another one
        offset = 0;
    }
    vrFS_update_fcb_in_dir(disk_layout, fcb);
    return SUCCESS;
        
}


int vrFS_readFile(DiskLayout* disk_layout, FCB* fcb, char* dest){
    int index = fcb->first_index;
    int read_bytes = 0 ,ret, size = BLOCK_SIZE;
    int bytes_left = fcb->size;
    
    while(read_bytes < bytes_left){
        if (bytes_left < BLOCK_SIZE){
            size = bytes_left; 
        }
        ret = disk_read_block(disk_layout, dest+read_bytes, size, index);
        if (ret != size) return READ_ERROR;
        bytes_left -= ret;
        read_bytes += ret;
        if (bytes_left != 0){
            index = disk_layout->fat[index];
        }

    }
    return SUCCESS;
}

