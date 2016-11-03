//
// Created by Stephen ASIEDU on 2016/11/02.
//
#include "../includes/Taskmaster.h"

static void     startingProcessInstruction(int pos, const char *progName){
    pid_t   wait;
    time_t  current;

    processes[pos].pid = processes[pos].program->startProcess();
    time(&processes[pos].reffStart);
    time(&current);
    wait = waitpid(processes[pos].pid, &processes[pos].status, WNOHANG);
    while (difftime(current, processes[pos].reffStart) < (double)processes[pos].program->getStartTime()){
        wait = waitpid(processes[pos].pid, &processes[pos].status, WNOHANG);
        if (wait != 0)
            break ;
        time(&current);
    }
    if (wait == 0){
        processes[pos].state = RUNNING;
        write(1, BLUE, strlen(BLUE));
        write(1, progName, strlen(progName));
        write(1, ": started", 9);
        write(1, RESET, strlen(RESET));
    }else{
        write(1, RED, strlen(RED));
        write(1, progName, strlen(progName));
        write(1, ": failed to started\n", 20);
        write(1, RESET, strlen(RESET));
    }
}

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
        startingProcessInstruction(pos, progName);
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
