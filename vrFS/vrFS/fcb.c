#include <stdio.h>
#include "../vrFS_basics/pool_allocator.h" 
#include "vrFS_constants.h"
#include "fcb.h"


#define FCB_SIZE sizeof(FCB)
#define FCB_MEMSIZE (sizeof(FCB) + sizeof(int)) // check
#define FCB_BLOCK_SIZE MAX_NUM_BLOCK*FCB_MEMSIZE

static char _fcb_block[FCB_BLOCK_SIZE];
static PoolAllocator _fcb_allocator;

FCB* FCB_init(){
    int res = PoolAllocator_init(& _fcb_allocator, FCB_SIZE, MAX_NUM_BLOCK, _fcb_block, FCB_BLOCK_SIZE);
    assert(!res);
    FCB* fcb = (FCB*)PoolAllocator_getBlock(& _fcb_allocator);
    fcb->list.prev = 0;
    fcb->list.next = 0;
    fcb->filename = 0;
    fcb->first_index = -1; 
    fcb->last_index = -1;
    fcb ->directory = 0;
    fcb->is_directory = -1;
    fcb->ownership = 0;
    fcb->size = 0;

    return fcb;
}

int FCB_free(FCB* fcb){
    return PoolAllocator_releaseBlock(&_fcb_allocator, fcb);
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
    printf("[filename: %s]\n[first block: %d - last block: %d]\n", fcb->filename, fcb->first_index, fcb->last_index);
    printf("[parent directory: %s]\n", fcb->directory->filename);
    printf("[is a directory: %d]\n", fcb->is_directory);
}