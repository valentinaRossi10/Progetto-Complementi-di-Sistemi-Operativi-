#include "vrSHELL_commands.h"
#include "vrSHELL_constants.h"
#include "vrSHELL_globals.h"
#include "vr_SHELL.h"

char* text = "ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentinaciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ciao sono valentina ";


int main(){
    vrSHELL_mappings();
    disk_layout = &disk;
    command_wrapper(SHELL_FORMAT, "vrFS_disk", 4096);

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
    fcb.is_directory = 0;
    vrFS_load_file(&disk, &fcb);
    vrFS_writeFile(&disk, &fcb, text, strlen(text));

    FCB directory;
    FCB_init(&directory);
    directory.filename = "cartella";
    directory.directory = &root;
    directory.ownership = "Valentina";
    directory.is_directory = 1;
    vrFS_load_file(&disk, &directory);

    FCB file_in_cartella;
    FCB_init(&file_in_cartella);
    file_in_cartella.filename = "FileInCartella.txt";
    file_in_cartella.directory = &directory;
    file_in_cartella.ownership = "Valentina";
    file_in_cartella.is_directory = 0;
    vrFS_load_file(&disk, &file_in_cartella);
    vrFS_writeFile(&disk, &file_in_cartella, text, strlen(text));

    FCB directory2;
    FCB_init(&directory2);
    directory2.filename = "cartella2";
    directory2.directory = &directory;
    directory2.ownership = "Valentina";
    directory2.is_directory = 1;
    vrFS_load_file(&disk, &directory2);

    vr_shell_init();
    
    printf("*********root : LS**************\n");
    command_wrapper(SHELL_LS);
    printf("**********ROOT : mkdir cartellaMK*********************\n");
    command_wrapper(SHELL_MKDIR, "cartellaMK");

    printf("**********ROOT : mkdir cartella/cartella2MK*********************\n");
    command_wrapper(SHELL_MKDIR, "cartella/cartella2MK");

    printf("**********ROOT : touch fileToccato.txt****************\n");
    command_wrapper(SHELL_TOUCH, "FileToccato.txt");

    
    printf("**********ROOT : touch ./cartella/cartella2MK/file2Toccato.txt****************\n");
    command_wrapper(SHELL_TOUCH, "./cartella/cartella2MK/File2Toccato.txt");
    
    printf("*********root : LS**************\n");
    command_wrapper(SHELL_LS);
    

    printf("**********ROOT: CAT cartella.FileInCartella.txt************\n");
    command_wrapper(SHELL_CAT, "./cartella/FileInCartella.txt");
    
    printf("*********root : LS root ./cartella**************\n");
    command_wrapper(SHELL_LS_WITH_ARG, "./cartella");
    
    printf("**********CAT PrimoFile.txt************\n");
    command_wrapper(SHELL_CAT, "PrimoFile.txt");
    
    printf("*********root : CD CARTELLA**************\n");
    command_wrapper(SHELL_CD, "cartella");
    printf("path : %s\n", path);


    printf("current directory : %s\n", currentFCB->filename);
    printf("**********cartella: APPEND lol a ../filetoccato*************\n");
    command_wrapper(SHELL_APPEND,"../FileToccato.txt", "lol");
    printf("**********cartella: CAT ../filetoccato*************\n");
    command_wrapper(SHELL_CAT,"../FileToccato.txt");
    
    printf("*********cartella : LS**************\n");
    command_wrapper(SHELL_LS);
    printf("**********CAT FileInCartella.txt************\n");
    command_wrapper(SHELL_CAT, "FileInCartella.txt");
    printf("*********cartella : CD . **************\n");
    command_wrapper(SHELL_CD, "./");
    printf("current directory : %s\n", currentFCB->filename);

    printf("*********cartella : CD .. **************\n");
    command_wrapper(SHELL_CD, "../");
    printf("current directory : %s\n", currentFCB->filename);
    printf("path : %s\n", path);
    printf("*********root: try remove cartella (not allowed)************\n");
    command_wrapper(SHELL_RM, "cartella");
    printf("******************root cat file toccato (should be  lol)*******************\n");
    command_wrapper(SHELL_CAT, "FileToccato.txt");
    printf("*********root : CD ./cartella **************\n");
    command_wrapper(SHELL_CD, "./cartella");
    printf("current directory : %s\n", currentFCB->filename);
    printf("path : %s\n", path);

    FCB file_in_cartella2;
    FCB_init(&file_in_cartella2);
    file_in_cartella2.filename = "FileInCartella2.txt";
    file_in_cartella2.directory = currentFCB;
    file_in_cartella2.ownership = "Valentina";
    file_in_cartella2.is_directory = 0;
    vrFS_load_file(&disk, &file_in_cartella2);
    vrFS_writeFile(&disk, &file_in_cartella2, text, strlen(text));
    printf("*********cartella : LS**************\n");
    command_wrapper(SHELL_LS);

    printf("*********cartella : CD ../cartella**************\n");
    command_wrapper(SHELL_CD, "../cartella");
        printf("path : %s\n", path);

    printf("current directory : %s\n", currentFCB->filename);
    printf("*********cartella : LS**************\n");
    command_wrapper(SHELL_LS);
    
    

    command_wrapper(SHELL_CLOSE);
}