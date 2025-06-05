#include "vrSHELL_commands.h"

ShellCommandType command_vector[MAX_NUM_FUNCTIONS];
int command_num_args[MAX_NUM_FUNCTIONS];
char* command_string_format[MAX_NUM_FUNCTIONS];
Command c;
Command* executing_command = &c;

void vrSHELL_mappings(){
    command_vector[SHELL_FORMAT] = vr_format;
    command_num_args[SHELL_FORMAT] = 2;
    command_string_format[SHELL_FORMAT] = "format %s %d";

    command_vector[SHELL_MKDIR] = vr_mkdir;
    command_num_args[SHELL_MKDIR] = 1;
    command_string_format[SHELL_MKDIR] = "mkdir %s";

    command_vector[SHELL_CD] = vr_cd;
    command_num_args[SHELL_CD] = 1;
    command_string_format[SHELL_CD] = "cd %s";

    command_vector[SHELL_TOUCH] = vr_touch;
    command_num_args[SHELL_TOUCH] = 1;
    command_string_format[SHELL_TOUCH] = "touch %s";

    command_vector[SHELL_CAT] = vr_cat;
    command_num_args[SHELL_CAT] = 1;
    command_string_format[SHELL_CAT] = "cat %s";

    command_vector[SHELL_LS] = vr_ls;
    command_num_args[SHELL_LS] = 0;
    command_string_format[SHELL_LS] = "ls";

    command_vector[SHELL_LS_WITH_ARG] = vr_ls;
    command_num_args[SHELL_LS_WITH_ARG] = 1;
    command_string_format[SHELL_LS_WITH_ARG] = "ls %s";


    command_vector[SHELL_APPEND] = vr_append;
    command_num_args[SHELL_APPEND] = 2; 
    command_string_format[SHELL_APPEND] = "append %s %s";

    command_vector[SHELL_RM] = vr_rm;
    command_num_args[SHELL_RM] = 1;
    command_string_format[SHELL_RM] = "rm %s";

    command_vector[SHELL_CLOSE] = vr_close;
    command_num_args[SHELL_CLOSE] = 0; // CHE COMANDO È ???
    command_string_format[SHELL_CLOSE] = "close";
}


//gets the arguments from the stack (variable number) and writes 
//them into executing_command->command_args 
int command_wrapper(int command_number, ...){
    memset(executing_command->command_args, 0, sizeof(executing_command->command_args));
    int num_args = command_num_args[command_number];
    va_list ap; 
    if (command_number < 0 || command_number > MAX_NUM_FUNCTIONS) return ERR_CMD_OUT_OF_RANGE;
    va_start(ap,command_number);
    for (int i = 0; i < num_args; i++){
        executing_command->command_args[i] = va_arg(ap, long int);
    }
    va_end(ap);
    executing_command->command_number = command_number;
    ShellCommandType cmd = command_vector[command_number];
    assert(cmd);
    (*cmd)();
    

    return executing_command->return_value;
}




void  vr_format() {
    printf("Called format()\n");
}






void vr_append() {
    printf("Called append()\n");
}


void vr_close(){

}