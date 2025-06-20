#include <stdio.h>
#include "vrFS_constants.h"
#include "fcb.h"
#include <string.h>


#define FCB_SIZE sizeof(FCB)
#define FCB_MEMSIZE (sizeof(FCB) + sizeof(int)) // check
#define FCB_BLOCK_SIZE MAX_NUM_BLOCK*FCB_MEMSIZE



void FCB_init(FCB* fcb){
    //inizializza i valori della struct fcb 
    fcb->filename[0] = '\0';
    fcb->first_index = -1; 
    fcb->last_index = -1;
    fcb->directory = -1;
    fcb->is_directory = -1;
    fcb->ownership = 0;
    fcb->size = 0;
}


void getFCB_by_block(DiskLayout* disk_layout, int block, FCB* fcb){
    char* buffer = (char*)malloc(sizeof(FCB));
    if (disk_read_block(disk_layout, buffer, sizeof(FCB), block) != sizeof(FCB)) {
        fprintf(stderr, "Errore nella lettura del blocco %d\n", block);
        exit(1);
    }
    memcpy(fcb, buffer, sizeof(FCB));
    free(buffer);
}

char* goto_memoryarea(DiskLayout* disk_layout, int block){
    return disk_layout->start_of_files + BLOCK_SIZE * block;
}


/*useful functions*/


void FCB_print(DiskLayout* disk_layout , FCB* fcb){
    //prints the content of the fcb
    //useful for debugging 
    printf("\n{\n");
    printf("\t[filename: %s]\n\t[first block: %d - last block: %d]\n", fcb->filename, fcb->first_index, fcb->last_index);
    
    if(fcb->directory != -1){
        FCB dir;
        getFCB_by_block(disk_layout, fcb->directory ,&dir);
        printf("\t[parent directory : %s]\n", dir.filename);
    } 
    else printf("\t[parent directory]\n");
    printf("\t[is a directory: %d]\n", fcb->is_directory);
    printf("\t[file size: %d]\n", fcb->size);
    printf("}\n");
}

void FCB_deepcopy(FCB* src, FCB* dest){
    //deep copy of src attributes into dest 
    assert(src && dest && "null pointers");
    dest->directory = src->directory;
    strcpy(dest->filename, src->filename);
    dest->first_index = src->first_index;
    dest->last_index = src->last_index;
    dest->is_directory = src->is_directory;
    dest->size = src->size;
    dest->ownership = src->ownership;
        
}

