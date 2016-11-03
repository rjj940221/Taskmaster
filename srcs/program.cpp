//
// Created by Stephen ASIEDU on 2016/10/31.
//

#include "../includes/program.h"
#include "../includes/odds.h"


using namespace std;

bool changeWorkingDir(string dir){
    struct stat info;
    char *newLoc = cstring(dir);
    if (stat(newLoc, &info) != 0) {
        recordLogError(newLoc, " Access not available");
        return false;
    }
    else if (info.st_mode & S_IFDIR) {// S_ISDIR() doesn't exist on my windows
        recordLogError(newLoc, " Is a directory");
        int re = chdir(newLoc);
        if (re == 0)
            return true;

    }
    return false;
}

Program::Program(string name, string cmd, int numProcess, int umask, string dir, bool autostart, int autorestart,
                 vector<int> exit_codes, int startRetries, int startTime,int stopsignal, int stopTime, string redirStdout,
                 string redirStderr, map<char*, char*> env) {
    this->name = name;
    this->cmd = cmd;
    this->numProcess = numProcess;
    this->newUmask = umask;
    this->dir = dir;
    this->autostart = autostart;
    this->autorestart = autorestart;
    this->exit_codes = exit_codes;
    this->startRetries = startRetries;
    this->startTime = startTime;
    this->stopsignal = stopsignal;
    this->stopTime = stopTime;
    this->redirStdout = redirStdout;
    this->redirStderr = redirStderr;
    this->env = env;
}

Program::~Program() {

}

pid_t Program::startProcess() {
    if (cmd.empty())
        return false;
    int status;
    pid_t re;
    int exere;
    char **args = split_string(cmd, ' ');

    pid_t pid = fork();
    if (pid == -1)    //error
    {
        return (-1);
    } else if (pid == 0)     //child
    {
        setpgid(0, 0);
        umask(newUmask);
        if (!redirStderr.empty())
            if (!redifd(redirStderr, 2)) {
                //cout <<"redir std err faild" << endl;
                exit(EXIT_FAILURE);
            }
        if (!redirStdout.empty())
            if (!redifd(redirStdout, 1)){
                //cout <<"redir std out faild tryed to re dit to |"<< redirStdout<<"|" << endl;
                exit(EXIT_FAILURE);
            }
        if (!dir.empty())
            if(!changeWorkingDir(dir)){
                //cout <<"redir working dir faild" << endl;
                exit(EXIT_FAILURE);
            }
        //cout << "checking env map"<<endl;
        for (map<char*, char*>::iterator it=env.begin(); it!=env.end(); ++it) {
            setenv(it->first, it->second, 1);
        }
        extern char **environ;
        exere = execve(args[0], args, environ);
        //cout << "execve returned " << exere << endl;
        exit(EXIT_FAILURE);
    } else {  //parent
        delete[] args;
        return pid;
    }
}

bool Program::checkExitStat(int status) {
    for (int i = 0; i < exit_codes.size(); ++i) {
        if (exit_codes.at(i) == status)
            return true;
    }
    return false;
}