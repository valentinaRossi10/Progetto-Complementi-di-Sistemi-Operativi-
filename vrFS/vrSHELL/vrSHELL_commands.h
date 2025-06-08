#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>
#include "vrSHELL_globals.h"
#include "vrSHELL_constants.h"


ShellCommandType command_vector[MAX_NUM_FUNCTIONS];
int command_num_args[MAX_NUM_FUNCTIONS];

typedef struct Command{
    int command_number;
    // long int so we can also store pointers
    long int command_args[MAX_NUM_ARGS];
    int return_value;
}Command;

 

void vrSHELL_mappings();
int command_wrapper(int command_number, ...);
void vr_format();
void vr_mkdir();
void vr_cd();
void vr_touch();
void vr_cat();
void vr_ls();
void vr_append();
void vr_rm();
void vr_close();