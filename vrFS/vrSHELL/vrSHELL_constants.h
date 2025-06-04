#pragma once
//shell commands' numbers

#define SHELL_FORMAT 1
#define SHELL_MKDIR 2
#define SHELL_CD 3
#define SHELL_TOUCH 4
#define SHELL_CAT 5
#define SHELL_LS 6
#define SHELL_APPEND 7
#define SHELL_RM 8
#define SHELL_CLOSE 9
#define SHELL_LS_WITH_ARG 10

//other constants

#define MAX_NUM_FUNCTIONS 10
#define MAX_NUM_ARGS 2

//errors

#define ERR_CMD_OUT_OF_RANGE -1
#define ERR_FILE_NOT_FOUND -2
#define ERR_FILE_NOT_A_DIR -3
#define ERR_FILE_IS_A_DIR -5
