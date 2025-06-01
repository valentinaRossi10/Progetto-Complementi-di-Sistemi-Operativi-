#pragma once
#include "../vrFS/fcb.h"
#include "../vrFS/vrFS.h"



extern FCB* currentFCB;
extern DiskLayout* disk_layout;
typedef void(*ShellCommandType)();
typedef struct Command Command;  
extern Command* executing_command;
