#pragma once

//shell commands' numbers
#define SHELL_FORMAT 0
#define SHELL_MKDIR 1
#define SHELL_CD 2
#define SHELL_TOUCH 3
#define SHELL_CAT 4
#define SHELL_LS 5
#define SHELL_APPEND 6
#define SHELL_RM 7
#define SHELL_CLOSE 8
#define SHELL_LS_WITH_ARG 9

//other constants
#define MAX_NUM_FUNCTIONS 10
#define MAX_NUM_ARGS 2

//errors
#define ERR_CMD_OUT_OF_RANGE -1
#define ERR_FILE_NOT_FOUND -2
#define ERR_FILE_NOT_A_DIR -3
#define ERR_FILE_IS_A_DIR -5
#define ERR_FORMAT -4
#define DISK_NOT_READY -6
#define APPEND_OVER_DISK_LIMIT -7 
#define INTERPRETER_ERR -8

