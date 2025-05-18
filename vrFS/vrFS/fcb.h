#include <stdio.h>
#include "../vrFS_basics/linked_list.h" 

typedef struct FCB{
    ListItem list; 
    char* filename;
    int first_index;
    int last_index;
    FCB* directory;
    int size;
    //permissions? 
    char* ownership;
    int is_directory; // 0 means it's not a directory 1 means it is a directory 
    ListHead sub_files; // linked list of its subdirectories 
}FCB;



FCB* FCB_init();