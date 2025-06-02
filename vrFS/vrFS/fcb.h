#pragma once
#include <assert.h>
#include <stdio.h>

typedef struct FCB{
    char* filename;
    int first_index;
    int last_index;
    struct FCB* directory;
    int size;
    //permissions? 
    char* ownership;
    int is_directory; // 0 means it's not a directory 1 means it is a directory 
}FCB;



void FCB_init(FCB* fcb);
int FCB_free(FCB* fcb);
void FCB_print(FCB* fcb);
void FCB_deepcopy(FCB* src, FCB* dest);