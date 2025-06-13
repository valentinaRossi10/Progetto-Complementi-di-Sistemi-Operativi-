#include "vrFS_dir.h"

void vrFS_update_fcb_in_dir(DiskLayout* disk_layout, FCB* updated_fcb) {
    // update a fcb on disk 
    FCB* dir = updated_fcb->directory;
    if (dir == NULL) return;

    int num_files = dir->size/sizeof(FCB);
    char* buffer = (char*)malloc(dir->size);

    
    int ret = vrFS_readFile(disk_layout, dir, buffer);
    assert(ret == SUCCESS && "read error");

    FCB* fcb_array = (FCB*)buffer;
    int found = 0;

    //scan the directory to find updated_fcb
    for (int i = 0; i < num_files; i++) {
        if (strcmp(fcb_array[i].filename, updated_fcb->filename) == 0) {
            fcb_array[i] = *updated_fcb; 
            found = 1;
            break;
        }
    }

    if (found) {
        
        int index = dir->first_index;
        int next;
        // clear the blocks occupied by the directory 

        while (disk_layout->fat[index] != -1) {
            next = disk_layout->fat[index];
            Disk block = vrFS_MemoryBlock_byFatIndex(disk_layout, next);
            vrFS_format_block(disk_layout, block);
            disk_layout->fat[index] = -1;
            disk_layout->free_table[next] = Free_Block;
            index = next;
        }
        //write back the updated values 

        dir->size = 0;
        dir->last_index = dir->first_index;
        ret = vrFS_writeFile(disk_layout, dir, (char*)fcb_array, num_files*sizeof(FCB));
        assert(ret == SUCCESS && "failed to write updated directory back to disk");
    }

    free(buffer);
}


void vrFS_remove_fcb_from_dir(DiskLayout* disk_layout, FCB* fcb_to_remove) {
    
    FCB* dir = fcb_to_remove->directory;
    if (dir== NULL) return;

    int num_files = dir->size/sizeof(FCB);
    char* buffer = (char*)malloc(dir->size); // buffer to store the directory content

    int ret = vrFS_readFile(disk_layout, dir, buffer);
    assert(ret == SUCCESS && "read error");

    
    FCB* fcb_array = (FCB*)buffer;

    // allocate a new buffer to store the updated directory (excluding the FCB to remove)
    char* new_buffer = (char*)malloc(dir->size); 
    FCB* new_fcb_array = (FCB*)new_buffer;

    int new_index = 0;
    // Copy all FCBs except the one to remove
    for (int i = 0; i < num_files; i++) { 
        if (strcmp(fcb_array[i].filename, fcb_to_remove->filename) != 0) {
            new_fcb_array[new_index] = fcb_array[i];
            new_index++;
        }
    }

    int i = dir->first_index;
    int next;

    //clear the blocks currently used by the directory 
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

    // write the updated directory content back to disk  
    ret = vrFS_writeFile(disk_layout, dir, new_buffer, new_index * sizeof(FCB));
    assert(ret == SUCCESS && "write error");

    free(buffer);
    free(new_buffer);
}


int vrFS_dir_search(DiskLayout* disk_layout, FCB* fcb_dir, FCB* returned_fcb, char* filename){
    //Looks for a file named 'filename' inside the directory 'fcb_dir'.
    //Reads the content of the directory (a sequence of the FCBs) from the disk.
    //if a matching fcb IS FOUND, it is copied into 'returned_fcb'
    //Otherwise, FILE_NOT_FOUND is returned otherwise.

    if (!fcb_dir->is_directory) return NOT_A_DIR;

    int num_files = fcb_dir->size / sizeof(FCB);
    char* dest = (char*)malloc(fcb_dir->size);

    int ret = vrFS_readFile(disk_layout, fcb_dir, dest);
    assert(ret == SUCCESS && "read error");

    FCB* fcb_fcb_arrayay = (FCB*)dest; // cast buffer to an fcb_arrayay of FCBs
    FCB* aux;

    for (int i = 0; i < num_files; i++){
        aux = fcb_fcb_arrayay+i;
        if (strcmp(filename, aux->filename) == 0) {
            FCB_deepcopy(aux, returned_fcb);
            return SUCCESS;
        }
    }
    return FILE_NOT_FOUND;

}




