#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>
#include "vrSHELL_globals.h"
#include "vrSHELL_constants.h"
#include "vrSHELL_functions.h"

typedef struct Command{
    int command_number;
    // long int so we can also store pointers
    long int command_args[MAX_NUM_ARGS];
    int return_value;
}Command;

void vrSHELL_mappings();
int command_wrapper(int command_number, ...);