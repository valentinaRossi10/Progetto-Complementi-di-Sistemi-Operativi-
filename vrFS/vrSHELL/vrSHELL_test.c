#include "vrSHELL_commands.h"
#include "vrSHELL_constants.h"
#include "vrSHELL_functions.h"
#include "vrSHELL_globals.h"

int main(){
    vrSHELL_mappings();
    command_wrapper(SHELL_CD,"file");
}