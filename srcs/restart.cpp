//
// Created by Stephen ASIEDU on 2016/11/02.
//

#include "../includes/Taskmaster.h"

static void    restartInstruction(const char *progName){
    int     pos = isProgramExist(progName);

    if (pos == -1){
        write(1, RED, strlen(RED));
        write(1, progName, strlen(progName));
        write(1, ": ERROR (no such process)\n", 26);
        write(1, RESET, strlen(RESET));
        return ;
    }
    if (processes[pos].state == RUNNING){
        stopInstruction(progName);
    }
    startInstruction(progName);
}

void    restartProcess(vector<string> param, LineEdit *shell){
    if (shell->shutdown){
        write(1, RED, strlen(RED));
        write(1, SHUTDOWN2, strlen(SHUTDOWN2));
        write(1, RESET, strlen(RESET));
        return ;
    }
    if (param.size() < 2){
        write(1, RED, strlen(RED));
        write(1, RSTARTERR1, strlen(RSTARTERR1));
        write(1, RSTARTERR2, strlen(RSTARTERR2));
        write(1, RSTARTERR3, strlen(RSTARTERR3));
        write(1, RSTARTERR4, strlen(RSTARTERR4));
        write(1, RSTARTERR5, strlen(RSTARTERR5));
        write(1, RESET, strlen(RESET));
        return ;
    }
    if (isAllPresent(param)){
        for(size_t i = 0; i < processes.size(); i++){
            restartInstruction(processes[i].program->getName().data());
        }
    }
    else{
        for(size_t i = 1; i < param.size(); i++){
            restartInstruction(param[i].data());
        }
    }
}