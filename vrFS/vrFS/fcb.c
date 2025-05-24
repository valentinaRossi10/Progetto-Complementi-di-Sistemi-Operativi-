#include <stdio.h>
#include "../vrFS_basics/pool_allocator.h" 
#include "vrFS_constants.h"
#include "fcb.h"


#define FCB_SIZE sizeof(FCB)
#define FCB_MEMSIZE (sizeof(FCB) + sizeof(int)) // check
#define FCB_BLOCK_SIZE MAX_NUM_BLOCK*FCB_MEMSIZE



void FCB_init(FCB* fcb){
    fcb->list.prev = 0;
    fcb->list.next = 0;
    fcb->filename = 0;
    fcb->first_index = -1; 
    fcb->last_index = -1;
    fcb ->directory = 0;
    fcb->is_directory = -1;
    fcb->ownership = 0;
    fcb->size = 0;
}

int FCB_free(FCB* fcb){
    return 0;
}

FCB* FCB_byFilename(ListHead* head, char* filename){
    ListItem* aux = head->first;
    while(aux){
        FCB* fcb = (FCB*)aux;
        if (fcb->filename == filename) return fcb;
        aux = aux->next;

    }
    return 0;
}

/*useful functions*/

void FCBPtrList_print(ListHead* head){
    ListItem* aux = head->first;
    printf("[");
    while(aux){
        FCB* fcb = (FCB*)aux;
        printf("%s", fcb->filename);
        aux = aux->next;
        if (aux) printf(", ");        
    }
    printf("]\n");
}

void FCB_print(FCB* fcb){
    printf("\n{\n");
    printf("\t[filename: %s]\n\t[first block: %d - last block: %d]\n", fcb->filename, fcb->first_index, fcb->last_index);
    if(fcb->directory) printf("\t[parent directory: %s]\n", fcb->directory->filename);
    else printf("\t[parent directory: root]\n");
    printf("\t[is a directory: %d]\n", fcb->is_directory);
    printf("\t[file size: %d]\n", fcb->size);
    printf("}\n");
}