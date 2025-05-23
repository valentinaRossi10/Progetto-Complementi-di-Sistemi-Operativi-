#include "vrFS.h"
#include "vrFS_disk.h"
#include <stdio.h>


int main(){
    printf("***********************TESTING DISK**************************\n");
    DiskLayout disk;
    disk_init(&disk);

    printf("\n*********BLOCK AT POSITION 0********* \n");
    Disk block = disk_MemoryBlock_byFatIndex(&disk,0); 
    int difference = block-disk.start_of_files;
    printf("difference (should be 0) : %d\n",difference);
    int index = disk_BlockIndex_byBlock(&disk, block);
    printf("index (should be 0) : %d\n", index);
    int fat_val = disk_FATValue_byMemoryBlock(&disk, block);
    printf("fat_val (should be 1) : %d\n", fat_val);
    FreeTableFlags free_val = disk_FreeTableValue_byMemoryBlock(&disk, block);
    printf("free_val (should be FreeBlock (1)) : %d\n",free_val);
    
    printf("\n*********BLOCK AT POSITION 100********* \n");
    Disk block2 = disk_MemoryBlock_byFatIndex(&disk,100); 
    difference = block2-disk.start_of_files;
    printf("difference (should be 100*4000) : %d\n",difference);
    index = disk_BlockIndex_byBlock(&disk, block2);
    printf("index (should be 100) : %d\n", index);
    fat_val = disk_FATValue_byMemoryBlock(&disk, block2);
    printf("fat_val (should be 101) : %d\n", fat_val);
    free_val = disk_FreeTableValue_byMemoryBlock(&disk, block2);
    printf("free_val (should be FreeBlock (1)) : %d\n",free_val);
   
}