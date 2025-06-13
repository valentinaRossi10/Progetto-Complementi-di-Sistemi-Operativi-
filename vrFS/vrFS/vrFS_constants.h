#pragma once

/*GLOBAL VALUES THAT NEED TO BE DEFINED AT RUNTIME (AFTER THE USER EXECUTES THE FORMAT COMMAND)*/
extern int MAX_NUM_BLOCK; // max number of blocks 
extern int FAT_SIZE; // fat dimension 
extern int TOTAL_SPACE; // space occupied by the blocks 
extern int DISK_SIZE; // total space occupied by blocks, fat table and free list  


/*CONSTANTS: SIZES*/
#define BLOCK_SIZE 4000
#define MAX_ALLOWED_BLOCKS 100000 // maximum number of blocks allowed (checked during format cmd execution)
#define MAX_FILENAME_LENGTH 100 


/*CONSTANTS: RETURN VALUES AND ERRORS*/
#define SUCCESS 1
#define NO_FREE_BLOCKS -1 
#define READ_ERROR -2
#define WRITE_ERROR -3
#define FILE_NOT_FOUND -4
#define DIRECTORY_NOT_EMPTY -5
#define NOT_A_DIR -6
#define DISK_INIT_ERROR -7





