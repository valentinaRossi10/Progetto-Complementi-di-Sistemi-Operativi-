#include "vrSHELL.h"

ShellCommandType command_vector[MAX_NUM_FUNCTIONS];
int command_num_args[MAX_NUM_FUNCTIONS];
char* command_string_format[MAX_NUM_FUNCTIONS];

void vrSHELL_mappings(){
    command_vector[SHELL_FORMAT] = format;
    command_num_args[SHELL_FORMAT] = 2;
    command_string_format[SHELL_FORMAT] = "format %s %d";

    command_vector[SHELL_MKDIR] = mkdir;
    command_num_args[SHELL_MKDIR] = 1;
    command_string_format[SHELL_MKDIR] = "mkdir %s";

    command_vector[SHELL_CD] = cd;
    command_num_args[SHELL_CD] = 1;
    command_string_format[SHELL_CD] = "cd %s";

    command_vector[SHELL_TOUCH] = touch;
    command_num_args[SHELL_TOUCH] = 1;
    command_string_format[SHELL_TOUCH] = "touch %s";

    command_vector[SHELL_CAT] = cat;
    command_num_args[SHELL_CAT] = 1;
    command_string_format[SHELL_CAT] = "cat %s";

    command_vector[SHELL_LS] = ls;
    command_num_args[SHELL_LS] = 0;
    command_string_format[SHELL_LS] = "ls";

    command_vector[SHELL_APPEND] = append;
    command_num_args[SHELL_APPEND] = 2; 
    command_string_format[SHELL_APPEND] = "append %s %s";

    command_vector[SHELL_RM] = rm;
    command_num_args[SHELL_RM] = 1;
    command_string_format[SHELL_RM] = "rm %s";

    command_vector[SHELL_CLOSE] = close;
    command_num_args[SHELL_CLOSE] = 0; // CHE COMANDO È ???
    command_string_format[SHELL_CLOSE] = "close";
}