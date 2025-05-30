#include "vrFS.h"
#include "fcb.h"
#include "vrFS_disk.h"
#include <stdio.h>
#include <string.h>

char* text = "ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ";

void test_1(){

    DiskLayout disk;
    disk_init(&disk);

    printf("\n*********BLOCK AT POSITION 0********* \n");
    Disk block = vrFS_MemoryBlock_byFatIndex(&disk,0); 
    int difference = block-disk.start_of_files;
    printf("difference (should be 0) : %d\n",difference);
    int index = vrFS_BlockIndex_byBlock(&disk, block);
    printf("index (should be 0) : %d\n", index);
    int fat_val = vrFS_FATValue_byMemoryBlock(&disk, block);
    printf("fat_val (should be 1) : %d\n", fat_val);
    FreeTableFlags free_val = vrFS_FreeTableValue_byMemoryBlock(&disk, block);
    printf("free_val (should be FreeBlock (1)) : %d\n",free_val);
    printf("\n*********CREATE A FILE********* \n");
    FCB fcb;
    FCB_init(&fcb);
    fcb.filename = "PrimoFile.txt";
    fcb.directory = 0;
    fcb.ownership = "Valentina";
    printf("loading file...\n");
    vrFS_load_file(&disk, &fcb);
    printf("file loaded\n");
    FCB_print(&fcb);
    printf("writing on file : %s\n", fcb.filename);
    vrFS_writeFile(&disk, &fcb, text, strlen(text));
    FCB_print(&fcb);
    char* dest = (char*)malloc(strlen(text)+1);
    printf("reading file content:\n");
    vrFS_readFile(&disk, &fcb, dest);
    printf("%s\n", dest);
    printf("\n*********************CREATING ANOTHER FILE*******************\n");

    FCB fcb2;
    FCB_init(&fcb2);
    fcb2.filename = "SecondoFile.txt";
    fcb2.directory = 0;
    fcb2.ownership = "Valentina";
    printf("loading file...\n");
    vrFS_load_file(&disk, &fcb2);
    printf("file loaded\n");
    FCB_print(&fcb2);
    char* buffer1 = (char*)malloc(2*BLOCK_SIZE + 55+1);
    memset(buffer1, 'v', 2*BLOCK_SIZE+55);
    buffer1[2*BLOCK_SIZE+55] = '\0';
    printf("writing on file : %s\n", fcb2.filename);

    vrFS_writeFile(&disk, &fcb2, buffer1, strlen(buffer1));
    FCB_print(&fcb2);
    dest = (char*)malloc(fcb2.size);
    printf("reading file content:\n");
    vrFS_readFile(&disk, &fcb2, dest);
    printf("%s\n", dest);
    free(buffer1);
    printf("**************WRITING AND READING AGAIN ON FIRST FILE********************\n");
    buffer1 = (char*)malloc(BLOCK_SIZE+1);
    memset(buffer1, '1', BLOCK_SIZE);
    buffer1[BLOCK_SIZE] = '\0';

    vrFS_writeFile(&disk, &fcb, buffer1, strlen(buffer1));
    FCB_print(&fcb);
    dest = (char*)malloc(fcb.size);
    printf("reading file content:\n");
    vrFS_readFile(&disk, &fcb, dest);
    printf("%s\n", dest);
    free(buffer1);

    printf("**************WRITING AND READING AGAIN ON SECOND FILE********************\n");
    buffer1 = (char*)malloc(BLOCK_SIZE+1);
    memset(buffer1, 'a', BLOCK_SIZE);
    buffer1[BLOCK_SIZE] = '\0';

    printf("writing on file : %s\n", fcb2.filename);
    vrFS_writeFile(&disk, &fcb2, buffer1, strlen(buffer1));
    FCB_print(&fcb2);
    dest = (char*)malloc(fcb2.size);
    printf("reading file content:\n");
    vrFS_readFile(&disk, &fcb2, dest);
    printf("%s\n", dest);

    
    

    
    printf("*************************disk format and shutdown*************************************\n");
    vrFS_format_disk(&disk);
    disk_shutdown(&disk);

}

void test_2(){
    printf("*************************TESTING DISK*************************\n");
    DiskLayout disk;
    disk_init(&disk);
    printf("*************************CREATING ROOT*************************\n");
    FCB root;
    FCB_init(&root);
    root.directory = NULL;
    root.filename = "root";
    root.is_directory = 1;
    root.ownership = "Valentina";
    vrFS_load_file(&disk, &root);
    FCB_print(&root);
    printf("*************************CREATING FILE 1*************************\n");
    FCB fcb;
    FCB_init(&fcb);
    fcb.filename = "PrimoFile.txt";
    fcb.directory = &root;
    fcb.ownership = "Valentina";
    vrFS_load_file(&disk, &fcb);
    vrFS_writeFile(&disk, &fcb, text, strlen(text));
    FCB_print(&fcb);
    FCB_print(&root);
    printf("*************************CREATING FILE 2*************************\n");
    
    FCB fcb2;
    FCB_init(&fcb2);
    fcb2.filename = "SecondoFile.txt";
    fcb2.directory = &root;
    fcb2.ownership = "Valentina";
    vrFS_load_file(&disk, &fcb2);
    char* buffer1 = (char*)malloc(2*BLOCK_SIZE + 55+1);
    memset(buffer1, 'v', 2*BLOCK_SIZE+55);
    buffer1[2*BLOCK_SIZE+55] = '\0';

    vrFS_writeFile(&disk, &fcb2, buffer1, strlen(buffer1));
    FCB_print(&fcb2);
    FCB_print(&root);

    printf("*************************EXPLORING ROOT*************************\n");
    FCB fcb_to_populate;
    int r = vrFS_dir_search(&disk, &root, &fcb_to_populate,"PrimoFile.txt");
    FCB_print(&fcb);
    if(r!= FILE_NOT_FOUND) FCB_print(&fcb_to_populate);

    printf("*************************DISK FORMAT AND SHUTDOWN******************************\n");
    vrFS_format_disk(&disk);
    disk_shutdown(&disk);


}
int main(){
    
    test_2();
}