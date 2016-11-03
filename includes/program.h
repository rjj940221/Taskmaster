#ifndef TASKMASTER_PROGRAM_H
#define TASKMASTER_PROGRAM_H

# include <iostream>
# include <string.h>
# include <stdio.h>
# include <ios>
# include <vector>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <libc.h>
# include <map>
# include <sstream>
# include <fstream>
# include "defines.h"



using namespace std;


class Program {
private:
    string name;
    string cmd;
    int numProcess;
    mode_t newUmask;
    string dir;
    bool autostart;
    int autorestart;
    vector<int> exit_codes;
    int startRetries;
    int startTime;
    int stopsignal;
    int stopTime;
    string redirStdout;
    string redirStderr;
    map<char *, char *> env;


public:
    Program();

    Program(string name, string cmd, int numProcess, int umask, string dir, bool autostart, int autorestart,
            vector<int> exit_codes, int startRetries, int startTime, int stopsignal, int stopTime, string redirStdout,
            string redirStderr, map<char *, char *> env);

    ~Program();

    string getName() { return this->name; };

    string getCmd() { return this->cmd; };

    int getNumProcess() { return this->numProcess; };
    //do umask
    string getDir() { return this->dir; };

    bool getAutostart() { return this->autostart; };

    int getAutorestart() { return this->autorestart; };

    vector<int> getExitCodes() { return this->exit_codes; };

    int getStartRetries() { return this->startRetries; };

    int getStartTime() { return this->startTime; };

    int getStopSignal() { return this->stopsignal; };

    int getStopTime() { return this->stopTime; };

    string getStdout() { return this->redirStdout; };

    string getStderr() { return this->redirStderr; };

    map<char*, char*> getEnv() { return this->env; };


    void setName(string name) { this->name = name; };

    void setCmd(string cmd) { this->cmd = cmd; };

    void setNumProcess(int numProc) { this->numProcess = numProc; };

    void setUmask(int newUmask) {this->newUmask = newUmask;};

    void setDir(string dir) { this->dir = dir; };

    void setAutostart(bool autostart) { this->autostart = autostart; };

    void setAutorestart(int autorestart) { this->autorestart = autorestart; };

    void setExitCodes(vector<int> codes) { this->exit_codes = codes; };

    void setStartRetries(int retries) { this->startRetries = retries; };

    void setStartTime(int startTime) { this->startTime = startTime; };

    void setStopSignal(int stopSignal) {this->stopsignal = stopSignal;};

    void setStopTime(int stopTime) { this->stopTime = stopTime; };

    void setStdout(string redirStdout) { this->redirStdout = redirStdout; };

    void setStderr(string redirStderr) { this->redirStderr = redirStderr; };

    void setEnv(map<char*, char*> env) { this->env = env; };

    pid_t startProcess();

    bool checkExitStat(int status);

    Program& operator=(Program arg);
};

#endif //TASKMASTER_PROGRAM_H