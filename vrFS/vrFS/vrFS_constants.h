#pragma once

//size

#define BLOCK_SIZE 4000
#define MAX_NUM_BLOCK 4096
#define TOTAL_SPACE BLOCK_SIZE*MAX_NUM_BLOCK
#define FAT_SIZE MAX_NUM_BLOCK*sizeof(int)
#define DISK_SIZE 2* FAT_SIZE + TOTAL_SPACE // 2 because free list and fat 


//errors

#define SUCCESS 1
#define NO_FREE_BLOCKS -1 
#define READ_ERROR -2
#define WRITE_ERROR -3
#define FILE_NOT_FOUND -4
#define DIRECTORY_NOT_EMPTY -5





