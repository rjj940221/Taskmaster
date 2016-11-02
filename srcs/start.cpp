//
// Created by Stephen ASIEDU on 2016/11/02.
//
#include "../includes/Taskmaster.h"

void    startInstruction(const char *progName){
    int     pos = isProgramExist(progName);

    if (pos == -1){
        write(1, RED, strlen(RED));
        write(1, progName, strlen(progName));
        write(1, ": ERROR (no such process)\n", 26);
        write(1, RESET, strlen(RESET));
        return ;
    }
    if (processes[pos].state == STOPPED){
        //start it
    }else if (processes[pos].state == RUNNING){
        write(1, RED, strlen(RED));
        write(1, progName, strlen(progName));
        write(1, ": ERROR (already started)\n", 26);
        write(1, RESET, strlen(RESET));
        return ;
    }else{
        write(1, RED, strlen(RED));
        write(1, progName, strlen(progName));
        write(1, ": ERROR (spawn error)\n", 22);
        write(1, RESET, strlen(RESET));
    }
}

void            startProcess(vector<string> param, LineEdit *shell){
    if (shell->shutdown){
        write(1, "temp", 4);
        return ;
    }
    if (param.size() < 2){
        write(1, RED, strlen(RED));
        write(1, STARTERR1, strlen(STARTERR1));
        write(1, STARTERR2, strlen(STARTERR2));
        write(1, STARTERR3, strlen(STARTERR3));
        write(1, STARTERR4, strlen(STARTERR4));
        write(1, RESET, strlen(RESET));
        return ;
    }
    if (isAllPresent(param)){
        cout << "starting all" << endl;
    }
    else{
        for(size_t i = 1; i < param.size(); i++){
            startInstruction(param[i].data());
        }
    }

}
