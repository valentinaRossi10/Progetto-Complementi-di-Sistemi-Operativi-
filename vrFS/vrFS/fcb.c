#include <stdio.h>
#include "vrFS_constants.h"
#include "fcb.h"


#define FCB_SIZE sizeof(FCB)
#define FCB_MEMSIZE (sizeof(FCB) + sizeof(int)) // check
#define FCB_BLOCK_SIZE MAX_NUM_BLOCK*FCB_MEMSIZE



void FCB_init(FCB* fcb){
    //inizializza i valori della struct fcb 
    fcb->filename = 0;
    fcb->first_index = -1; 
    fcb->last_index = -1;
    fcb ->directory = 0;
    fcb->is_directory = -1;
    fcb->ownership = 0;
    fcb->size = 0;
}



/*useful functions*/


void FCB_print(FCB* fcb){
    //prints the content of the fcb
    //useful for debugging 
    printf("\n{\n");
    printf("\t[filename: %s]\n\t[first block: %d - last block: %d]\n", fcb->filename, fcb->first_index, fcb->last_index);
    if(fcb->directory) printf("\t[parent directory: %s]\n", fcb->directory->filename);
    else printf("\t[parent directory]\n");
    printf("\t[is a directory: %d]\n", fcb->is_directory);
    printf("\t[file size: %d]\n", fcb->size);
    printf("}\n");
}

void FCB_deepcopy(FCB* src, FCB* dest){
    //deep copy of src attributes into dest 
    assert(src && dest && "null pointers");
    dest->directory = src->directory;
    dest->filename = src->filename;
    dest->first_index = src->first_index;
    dest->last_index = src->last_index;
    dest->is_directory = src->is_directory;
    dest->size = src->size;
    dest->ownership = src->ownership;
        
}