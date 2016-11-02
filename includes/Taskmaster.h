//
// Created by Stephen ASIEDU on 2016/11/01.
//

#ifndef TASKMASTER_TASKMASTER_H
#define TASKMASTER_TASKMASTER_H

#include "LineEdit.h"
#include <regex>
#include <iterator>
#include "program.h"


typedef struct      s_Process{
    pid_t           pid;
    Program         program;
    int             status;
    time_t          reffStart;
    time_t          reffKill;
    bool            kill;
    int             numRetry;
}                   t_Process;

extern vector<t_Process> processes;

//terminol instructions
void    processInstruction(string line, LineEdit *shell);
void    startProcess(vector<string> param, LineEdit *shell);
void    stopProcess(vector<string> param, LineEdit *shell);
void    restartProcess(vector<string> param, LineEdit *shell);
void    helpProcess(vector<string> param, LineEdit *shell);
bool    isAllPresent(vector<string> param);


//controller functions
void initProcecces(string file);

#endif //TASKMASTER_TASKMASTER_H
