//
// Created by Stephen ASIEDU on 2016/11/02.
//

#include "../includes/Taskmaster.h"

static void     restartAlways(size_t index){
    if (processes[index].numRetry < processes[index].program->getStartRetries()){
        processes[index].pid = processes[index].program->startProcess();
        processes[index].state = STARTING;
        time(&processes[index].reffStart);
        processes[index].numRetry++;
    }
}

static void     restartUnexpected(size_t index){
    if (!processes[index].program->checkExitStat(WEXITSTATUS(processes[index].status))){
        if (processes[index].numRetry < processes[index].program->getStartRetries()){

            char proname[255];
            char msg[255];

            sprintf(proname, "program %s exited: ", processes[index].program->getName().data());
            sprintf(msg,"exitstatus %d", WEXITSTATUS(processes[index].status));
            recordLogError(proname, msg);


            processes[index].pid = processes[index].program->startProcess();
            processes[index].state = STARTING;
            time(&processes[index].reffStart);
            processes[index].numRetry++;
        }else
            processes[index].state = BACKOFF;
    }else
        processes[index].state = BACKOFF;
}

static void     checkKill(size_t index){
    pid_t   wait;
    time_t  current;

    wait = waitpid(processes[index].pid, &processes[index].status, WNOHANG);
    if (wait == 0){
        time(&current);
        if (difftime(current, processes[index].reffKill) >= (double)processes[index].program->getStopTime()){
            kill(processes[index].pid, SIGKILL);
        }
    }else{
        processes[index].state = STOPPED;
        processes[index].kill = false;
    }
}

static void     checkStartProcess(size_t index){
    time_t  current;
    pid_t   wait;

    if (processes[index].state == STOPPED || processes[index].state == FATAL || processes[index].state == NOSTART || processes[index].state == BACKOFF || processes[index].state == DEAD)
        return ;
    if (processes[index].pid == -1){
        recordLogError(processes[index].program->getName(), "Fork failed.");
        processes[index].state = FATAL;
        return ;
    }
    wait = waitpid(processes[index].pid, &processes[index].status, WNOHANG);
    if (wait == -1){
        recordLogError(processes[index].program->getName(), "Process does not exist.");
        processes[index].state = FATAL;
    }else if (wait != 0){
        if (processes[index].program->getAutorestart() == ALWAYS)
            restartAlways(index);
        else if (processes[index].program->getAutorestart() == UNEXPECTED)
            restartUnexpected(index);
        else{
            processes[index].state = BACKOFF;
        }
    }else{
        time(&current);
        if (difftime(current, processes[index].reffStart) >= (double)processes[index].program->getStartTime()){
            processes[index].state = RUNNING;
        }
    }
}

void            controllerCheck(){
    for (size_t i= 0; i < processes.size(); i++){
        if (processes[i].kill){
            checkKill(i);
        }else{
            checkStartProcess(i);
        }
    }
}