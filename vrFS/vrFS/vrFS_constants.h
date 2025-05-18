#pragma once

//size

#define BLOCK_SIZE 4000
#define MAX_NUM_BLOCK 4096
#define TOTAL_SPACE BLOCK_SIZE*MAX_NUM_BLOCK
#define FAT_SIZE MAX_NUM_BLOCK*sizeof(int)
#define DISK_SIZE 2* FAT_SIZE + TOTAL_SPACE // 2 because free list and fat 


//errors

#define NO_FREE_BLOCKS -1 


