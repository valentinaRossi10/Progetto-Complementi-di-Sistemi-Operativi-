#include "vrSHELL_commands.h"
#include "../vrFS/vrFS.h"

void vr_ls(){
    
    int num_files = currentFCB->size / sizeof(FCB);
    char* dest = (char*)malloc(currentFCB->size);
    int ret = vrFS_readFile(disk_layout, currentFCB, dest);
    assert(ret == SUCCESS && "read error");
    FCB* fcb_array = (FCB*)dest;
    FCB* aux;
    //char** result = (char**)malloc(sizeof(char*)*num_files);
    for (int i = 0; i < num_files; i++){
        //result[i] = (char*)malloc(MAX_FILENAME_LENGTH);
        aux = fcb_array+i;
        printf("%s\n",aux->filename);
        //strcpy(result[i], aux->filename);
        
    }
    executing_command->return_value = 1;


}

