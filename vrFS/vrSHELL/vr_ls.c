#include "vrSHELL_commands.h"
#include "../vrFS/vrFS.h"

void vr_ls(){
    
    int num_files = currentFCB->size / sizeof(FCB);
    char* dest = (char*)malloc(currentFCB->size);
    int ret = vrFS_readFile(disk_layout, currentFCB, dest);
    assert(ret == SUCCESS && "read error");
    FCB* fcb_array = (FCB*)dest;
    FCB* aux;
    for (int i = 0; i < num_files; i++){
        aux = fcb_array+i;
        printf("%s\n",aux->filename);
        
    }
    executing_command->return_value = SUCCESS;


}

