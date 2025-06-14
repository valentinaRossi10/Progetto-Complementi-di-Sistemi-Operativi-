#pragma once
#include "../vrFS/fcb.h"
#include "../vrFS/vrFS.h"



extern FCB* currentFCB; // keeps track of which is the fcb of the file we are currently in 
extern DiskLayout* disk_layout; 

typedef struct Command Command;  
extern Command* executing_command; // which command is currently being executed 
