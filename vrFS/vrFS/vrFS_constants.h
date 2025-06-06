#pragma once

//size

extern int MAX_NUM_BLOCK;
extern int FAT_SIZE;
extern int TOTAL_SPACE;
extern int DISK_SIZE;

#define BLOCK_SIZE 4000
#define MAX_ALLOWED_BLOCKS 100000
#define MAX_FILENAME_LENGTH 100


//errors

#define SUCCESS 1
#define NO_FREE_BLOCKS -1 
#define READ_ERROR -2
#define WRITE_ERROR -3
#define FILE_NOT_FOUND -4
#define DIRECTORY_NOT_EMPTY -5
#define NOT_A_DIR -6
#define DISK_INIT_ERROR -7





