//
// Created by Stephen ASIEDU on 2016/10/31.
//

#ifndef TASKMASTER_PROGRAM_H
#define TASKMASTER_PROGRAM_H


class Program {
private:
    string      name;
    string      cmd;
    int         numProcess;
    //do umask
    string      dir;
    bool        autostart;
    int         autorestart;
    //exit codes
    int         startRetries;
    int         startTime;
    //stop signal
    int         stopTime;
    string      stdout;
    string      stderr;
    //env

public:
    Program();
    ~Program();
    string      getName(){return this->name;};
    string      getCmd(){ return this->cmd;};
    int         getNumProcess(){ return this->numProcess;};
    //do umask
    string      getDir(){ return this->dir;};
    bool        getAutostart(){ return this->autostart;};
    int         getAutorestart(){ return this->autorestart;};
    //exit codes
    int         getStartRetries(){ return this->startRetries;};
    int         getStartTime(){ return this->startTime;};
    //stop signal
    int         getStopTime(){ return this->stopTime;};
    string      getStdout(){ return this->stdout;};
    string      getStderr(){ return this->stderr;};
    //env


    void        setName(string name){this->name = name;};
    void        setCmd(string cmd){this->cmd = cmd;};
    void        setNumProcess(int numProc){this->numProcess = numProc;};
    //do umask
    void        setDir(string dir){this->dir = dir;};
    void        setAutostart(bool autostart){this->autostart = autostart;};
    void        setAutorestart(int autorestart){this->autorestart = autorestart;};
    //exit codes
    void        setStartRetries(int retries){this->startRetries = retries;};
    void        setStartTime(int startTime){this->startTime = startTime;};
    //stop signal
    void        setStopTime(int stopTime){this->stopTime = stopTime;};
    void        setStdout(string stdout){this->stdout = stdout;};
    void        setStderr(string stderr){this->stderr = stderr;};
    //env
};


#endif //TASKMASTER_PROGRAM_H
