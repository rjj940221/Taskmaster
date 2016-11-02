//
// Created by Stephen ASIEDU on 2016/11/02.
//

#include "../includes/Taskmaster.h"

vector<t_Process> processes = *new vector<t_Process>;

int     main(){
    LineEdit    shell;
    bool        ret;

    shell.startShell();
    while (!shell.exitTaskmaster){
        ret = shell.readCharacter();
        if (ret){
            processInstruction(shell.getLine(), &shell);
            shell.startShell();
        }
        //controllerCheck();
    }
    return (0);
}