#pragma once
#include <assert.h>
#include <stdio.h>
#include "../vrFS_basics/linked_list.h" 

typedef struct FCB{
    ListItem list; 
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
FCB* FCB_byFilename(ListHead* head, char* filename);
void FCBPtrList_print(ListHead* head);
void FCB_print(FCB* fcb);