//
// Created by Stephen ASIEDU on 2016/11/02.
//

#include "../includes/Taskmaster.h"

static void     checkStartProcess(size_t index){
    time_t  current;
    pid_t   wait;

    wait = waitpid(processes[index].pid, &processes[index].status, WNOHANG);
    if (wait == -1){
        /*if (processes[index].numRetry < processes[index].program.getStartRetries() && processes[index].program.getAutorestart() ==  ALWAYS){
            processes[index].pid = processes[index].program.startProcess();
            processes[index].state = STARTING;
            time(&processes[index].reffStart);
            processes[index].numRetry++;
        }else*/
            processes[index].state = FATAL;
        string err = processes[index].program.getStderr();
        int fd = open(err.data(), O_RDWR | O_APPEND | O_CREAT | 0755);
        write(fd, "Failed to fork\n", 15);
        close(fd);
    }else if (wait != 0){
        vector<int>     exitCodes = processes[index].program.getExitCodes();
        for (int i = 0; i < exitCodes.size(); i++){
            if (exitCodes.at(i) == processes[index].status && processes[index].program.getAutorestart() !=  NEVER){
                if (processes[index].numRetry < processes[index].program.getStartRetries()){
                    processes[index].pid = processes[index].program.startProcess();
                    processes[index].state = STARTING;
                    time(&processes[index].reffStart);
                    processes[index].numRetry++;
                }
            }else
                processes[index].state = DEAD;
        }
    }else{
        time(&current);
        if (difftime(current, processes[index].reffStart) >= (double)processes[index].program.getStartTime()){
            processes[index].state = RUNNING;
        }
    }
}

void            controllerCheck(){
    for (size_t i= 0; i < processes.size(); i++){
        if (processes[i].kill){
            //work on kill
        }else {
            checkStartProcess(i);
        }
    }
}