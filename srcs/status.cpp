//
// Created by Stephen ASIEDU on 2016/11/03.
//
#include "../includes/Taskmaster.h"

using namespace std;

static void     startStatus(size_t index){
    write(1, CYAN, strlen(CYAN));
    printf("%-30s %-11s\n", processes[index].program->getName().data(), "STARTING");
    write(1, RESET, strlen(RESET));
}

static void     runningStatus(size_t index){
    double   hrs = 0;
    double   mins = 0;
    double   secs = 0;
    double  diff;
    time_t  current;

    time(&current);
    diff = difftime(current, processes[index].reffStart);
    secs = fmod(diff, 60);
    mins = diff / 60;
    mins = fmod(mins, 60);
    hrs = fmod(fmod(diff/60, 60), 60);
    write(1, BLUE, strlen(BLUE));
    printf("%-30s %-11s pid %d, uptime %d:%02d:%02d\n", processes[index].program->getName().data(), "RUNNING",
           processes[index].pid, (int)hrs, (int)mins, (int)secs);
    write(1, RESET, strlen(RESET));
}

static void     fatalStatus(size_t index){
    write(1, RED, strlen(RED));
    printf("%-30s %-11s Exited too quickly / Failed to execute (taskmaster.log may have details)\n", processes[index].program->getName().data(), "FATAL");
    write(1, RESET, strlen(RESET));
}

static void     backoffStatus(size_t index){
    write(1, MAGENTA, strlen(MAGENTA));
    printf("%-30s %-11s Exited too quickly (taskmaster.log may have details)\n", processes[index].program->getName().data(), "BACKOFF");
    write(1, RESET, strlen(RESET));
    processes[index].state = FATAL;
}

static void     stoppedStatus(size_t index){
    struct tm  tstruct;
    char       buf[90];

    tstruct = *localtime(&processes[index].reffKill);
    bzero(buf, sizeof(char) * 90);
    strftime(&buf[0], sizeof(buf), "%b %d %Y %I %M %p", &tstruct);
    write(1, BLUE, strlen(BLUE));
    printf("%-30s %-11s %s\n", processes[index].program->getName().data(), "STOPPED", buf);
    write(1, RESET, strlen(RESET));
}

void            allStatus(){
    for (size_t i = 0; i < processes.size(); i++){
        if (processes[i].state == STARTING)
            startStatus(i);
        else if (processes[i].state == RUNNING)
            runningStatus(i);
        else if (processes[i].state == FATAL)
            fatalStatus(i);
        else if (processes[i].state == BACKOFF)
            backoffStatus(i);
        else if (processes[i].state == STOPPED)
            stoppedStatus(i);

    }
}

void            statusProcess(vector<string> param, LineEdit *shell){
    if (shell->shutdown){
        write(1, RED, strlen(RED));
        write(1, SHUTDOWN2, strlen(SHUTDOWN2));
        write(1, RESET, strlen(RESET));
        return ;
    }
    if (param.size() < 2 || isAllPresent(param)){
        allStatus();
    }else{
        for(size_t i = 1; i < param.size(); i++){
            int     pos = isProgramExist(param[i].data());

            if (pos == -1){
                write(1, RED, strlen(RED));
                write(1, param[i].data(), strlen(param[i].data()));
                write(1, ": ERROR (no such process)\n", 26);
                write(1, RESET, strlen(RESET));
            }else{
                if (processes[pos].state == STARTING)
                    startStatus((size_t)pos);
                else if (processes[pos].state == RUNNING)
                    runningStatus((size_t)pos);
                else if (processes[pos].state == FATAL)
                    fatalStatus((size_t)pos);
                else if (processes[pos].state == BACKOFF)
                    backoffStatus((size_t)pos);
                else if (processes[pos].state == STOPPED)
                    stoppedStatus((size_t)pos);
            }
        }
    }
}