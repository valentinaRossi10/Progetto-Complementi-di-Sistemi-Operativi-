#include "vrFS_dir.h"

void vrFS_update_fcb_in_dir(DiskLayout* disk_layout, FCB* updated_fcb) {
    FCB* dir = updated_fcb->directory;
    if (dir == NULL) return;

    int num_files = dir->size / sizeof(FCB);
    char* buffer = malloc(dir->size);
    int ret = vrFS_readFile(disk_layout, dir, buffer);
    assert(ret == SUCCESS);

    FCB* arr = (FCB*)buffer;
    int found = 0;

    for (int i = 0; i < num_files; i++) {
        if (strcmp(arr[i].filename, updated_fcb->filename) == 0) {
            arr[i] = *updated_fcb; 
            found = 1;
            break;
        }
    }

    if (found) {
        
        int index = dir->first_index;
        int next;

        while (disk_layout->fat[index] != -1) {
            next = disk_layout->fat[index];
            Disk block = vrFS_MemoryBlock_byFatIndex(disk_layout, next);
            // Format del blocco, formatto il next perchè il primo non deve essere 
            vrFS_format_block(disk_layout, block);
            disk_layout->fat[index] = -1;
            disk_layout->free_table[next] = Free_Block;
            index = next;
        }

        dir->size = 0;
        dir->last_index = dir->first_index;
        ret = vrFS_writeFile(disk_layout, dir, (char*)arr, num_files*sizeof(FCB));
        assert(ret == SUCCESS && "failed to write updated directory back to disk");
    }

    free(buffer);
}


void vrFS_remove_fcb_from_dir(DiskLayout* disk_layout, FCB* fcb_to_remove) {
    FCB* dir = fcb_to_remove->directory;
    if (dir!= NULL) return;

    int num_files = dir->size/sizeof(FCB);
    char* buffer = (char*)malloc(dir->size);
    int ret = vrFS_readFile(disk_layout, dir, buffer);
    assert(ret == SUCCESS && "read error");

    FCB* arr = (FCB*)buffer;

    //nuovo buffer senza l'FCB da rimuovere
    char* new_buffer = (char*)malloc(dir->size);
    FCB* new_arr = (FCB*)new_buffer;

    int new_index = 0;
    for (int i = 0; i < num_files; i++) {
        if (strcmp(arr[i].filename, fcb_to_remove->filename) != 0) {
            new_arr[new_index] = arr[i];
            new_index++;
        }
    }

    int i = dir->first_index;
    int next;
    while (disk_layout->fat[i] != -1) {
        next = disk_layout->fat[i];
        Disk block = vrFS_MemoryBlock_byFatIndex(disk_layout, next);
        vrFS_format_block(disk_layout, block);
        disk_layout->fat[i] = -1;
        disk_layout->free_table[next] = Free_Block;
        i = next;
    }

    dir->size = 0;
    dir->last_index = dir->first_index;

    // aggiorna la directory senza il file rimosso
    ret = vrFS_writeFile(disk_layout, dir, new_buffer, new_index * sizeof(FCB));
    assert(ret == SUCCESS && "write error");

    free(buffer);
    free(new_buffer);
}




int vrFS_dir_search(DiskLayout* disk_layout, FCB* fcb_dir, FCB* returned_fcb, char* filename){
    int num_files = fcb_dir->size / sizeof(FCB);
    char* dest = (char*)malloc(fcb_dir->size);
    int ret = vrFS_readFile(disk_layout, fcb_dir, dest);
    assert(ret == SUCCESS && "read error");
    FCB* fcb_array = (FCB*)dest;
    FCB* aux;
    for (int i = 0; i < num_files; i++){
        aux = fcb_array+i;
        if (strcmp(filename, aux->filename) == 0) {
            //deep copy
            returned_fcb->directory = aux->directory;
            returned_fcb->filename = aux->filename;
            returned_fcb->first_index = aux->first_index;
            returned_fcb->last_index = aux->last_index;
            returned_fcb->is_directory = aux->is_directory;
            returned_fcb->size = aux->size;
            returned_fcb->ownership = aux->ownership;
            return SUCCESS;
        }
    }
    return FILE_NOT_FOUND;

}

