//
// Created by Stephen ASIEDU on 2016/10/31.
//

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

#define NEVER 0
#define ALWAYS 1
#define UNEXPECTED 2


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
    //stop signal
    int stopTime;
    string redirStdout;
    string redirStderr;
    int numProcessesRunning;
    vector<pid_t> runningProcesses;
    map<char*,char*> env;
    bool    checkExitStat(int status);

public:
    Program();

    Program(string name, string cmd, int numProcess, int umask, string dir, bool autostart, int autorestart, vector<int> exit_codes, int startRetries, int startTime, int stopTime, string redirStdout, string redirStderr, map<char*, char*> env);

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

    //stop signal
    int getStopTime() { return this->stopTime; };

    string getStdout() { return this->redirStdout; };

    string getStderr() { return this->redirStderr; };
    //env


    void setName(string name) { this->name = name; };

    void setCmd(string cmd) { this->cmd = cmd; };

    void setNumProcess(int numProc) { this->numProcess = numProc; };

    //do umask
    void setDir(string dir) { this->dir = dir; };

    void setAutostart(bool autostart) { this->autostart = autostart; };

    void setAutorestart(int autorestart) { this->autorestart = autorestart; };

    void setExitCodes(vector<int> codes) { this->exit_codes = codes; };

    void setStartRetries(int retries) { this->startRetries = retries; };

    void setStartTime(int startTime) { this->startTime = startTime; };

    //stop signal
    void setStopTime(int stopTime) { this->stopTime = stopTime; };

    void setStdout(string redirStdout) { this->redirStdout = redirStdout; };

    void setStderr(string redirStderr) { this->redirStderr = redirStderr; };

    //env
    pid_t startProcess();

    //bool    checkExitStat(int status);
};

#endif //TASKMASTER_PROGRAM_H