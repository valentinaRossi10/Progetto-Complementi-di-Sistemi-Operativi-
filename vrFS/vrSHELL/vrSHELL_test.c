#include "vrSHELL_commands.h"
#include "vrSHELL_constants.h"
#include "vrSHELL_globals.h"

char* text = "ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ";
FCB* currentFCB;
DiskLayout disk;
DiskLayout* disk_layout;

int main(){
    disk_layout = &disk;
    disk_init(disk_layout);
    FCB root;
    FCB_init(&root);
    root.directory = NULL;
    root.filename = "root";
    root.is_directory = 1;
    root.ownership = "Valentina";
    vrFS_load_file(&disk, &root);
    currentFCB = &root;

    FCB fcb;
    FCB_init(&fcb);
    fcb.filename = "PrimoFile.txt";
    fcb.directory = &root;
    fcb.ownership = "Valentina";
    vrFS_load_file(&disk, &fcb);
    vrFS_writeFile(&disk, &fcb, text, strlen(text));


    disk_init(disk_layout);
    vrSHELL_mappings();
    command_wrapper(SHELL_LS);
    
}