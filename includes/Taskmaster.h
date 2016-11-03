//
// Created by Stephen ASIEDU on 2016/11/01.
//

#ifndef TASKMASTER_H
# define TASKMASTER_H

#include "LineEdit.h"
#include <regex>
#include <iterator>
#include <fcntl.h>
#include "program.h"
#include "odds.h"


typedef struct s_Process {
    pid_t pid;
    Program *program;
    int status;
    int state;
    time_t reffStart;
    time_t reffKill;
    bool kill;
    int numRetry;
} t_Process;

extern int pop;
extern vector<t_Process> processes;

//terminol instructions
void processInstruction(string line, LineEdit *shell);

void startProcess(vector<string> param, LineEdit *shell);

void stopProcess(vector<string> param, LineEdit *shell);

void restartProcess(vector<string> param, LineEdit *shell);

void helpProcess(vector<string> param, LineEdit *shell);

bool isAllPresent(vector<string> param);


//controller functions
void readFile(string file, bool init);

void controllerCheck();

int isProgramExist(const char *progName);

void startInstruction(const char *progName);

void stopInstruction(const char *progName);


#endif //TASKMASTER_TASKMASTER_H
