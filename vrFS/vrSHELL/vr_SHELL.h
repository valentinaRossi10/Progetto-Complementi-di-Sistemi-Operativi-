#pragma once
#include "vrSHELL_commands.h"
#include "vrSHELL_constants.h"
#include "vrSHELL_globals.h"


extern char* path;
extern int path_size;

typedef enum {
    up = 1,
    down = -1
} Direction;


void vr_shell_init();

void vr_shell_loop();

void vr_shell_prompt();

int vr_shell_interpreter(char* cmd);

void vr_shell_update_path();
