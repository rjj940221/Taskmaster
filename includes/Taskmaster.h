//
// Created by Stephen ASIEDU on 2016/11/01.
//

#ifndef TASKMASTER_H
# define TASKMASTER_H

#include "LineEdit.h"
#include <regex>
#include <iterator>
#include <fcntl.h>
#include <signal.h>
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

extern char* g_file;

extern vector<t_Process> processes;

extern time_t taskmasterTime;

//terminol instructions
void processInstruction(string line, LineEdit *shell);

void startProcess(vector<string> param, LineEdit *shell);

void stopProcess(vector<string> param, LineEdit *shell);

void restartProcess(vector<string> param, LineEdit *shell);

void helpProcess(vector<string> param, LineEdit *shell);

bool isAllPresent(vector<string> param);

//controller functions

bool readFile(string file, bool init);

void controllerCheck();

int isProgramExist(const char *progName);

void startInstruction(const char *progName);

void stopInstruction(const char *progName);

void controllerCheck();

void allStatus();

void statusProcess(vector<string> param, LineEdit *shell);

void shutdownProcess(vector<string> param, LineEdit *shell);

void exit();

//log functions
void recordLogError(string prog, string issue);

void recordLogProcess(string prog, string process);

#endif //TASKMASTER_TASKMASTER_H
