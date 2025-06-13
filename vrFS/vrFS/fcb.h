#pragma once
#include <assert.h>
#include <stdio.h>

typedef struct FCB{
    char* filename;
    int first_index;
    int last_index;
    struct FCB* directory;
    int size;
    char* ownership;
    int is_directory; // boolean value, 1 means it is a directory 0 means it is a regular file  
}FCB;


void FCB_init(FCB* fcb);
void FCB_print(FCB* fcb);
void FCB_deepcopy(FCB* src, FCB* dest);