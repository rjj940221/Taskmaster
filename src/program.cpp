//
// Created by Stephen ASIEDU on 2016/10/31.
//

#include "../includes/program.h"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

void split(const string &s, char delim, vector <string> &elems) {
    stringstream ss;
    ss.str(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
}

vector <string> split(const string &s, char delim) {
    vector <string> elems;
    split(s, delim, elems);
    return elems;
}

char *cstring(string in) {
    char *out = new char[in.length() + 1];
    strcpy(out, in.c_str());

    return (out);
}

Program::Program(string name, string cmd, int numProcess, string dir, bool autostart, int autorestart,
                 vector<int> exit_codes, int startRetries, int startTime, int stopTime, string redirStdout,
                 string redirStderr) {
    this->name = name;
    this->cmd = cmd;
    this->numProcess = numProcess;
    this->numProcessesRunning = 0;
    //do umask
    this->dir = dir;
    this->autostart = autostart;
    this->autorestart = autorestart;
    this->exit_codes = exit_codes;
    this->startRetries = startRetries;
    this->startTime = startTime;
    //stop signal
    this->stopTime = stopTime;
    this->redirStdout = redirStdout;
    this->redirStderr = redirStderr;
}

Program::~Program() {

}

bool redifd(string file, int fd) {
    int newfd;
    char *newLoc = cstring(file);
    bool re;

    cout << "tring to open " << newLoc << endl;
    newfd = open(newLoc, O_RDWR);
    if (newfd < 0) {
        cout << "it bork" << endl;
        re = false;
    } else {
        if (dup2(fd, newfd) == -1)
            re = false;
        else {
            cout << "it file open" << endl;
            re = true;
        }
    }
    delete[](newLoc);
    return re;
}

bool Program::startProcess() {
    if (cmd.empty())
        return false;
    pid_t pid = fork();
    int status;
    bool re;
    int     exere;
    char    *newcmd = cstring(cmd);
    char    *args[3];
    args[0] = "/bin/ls";
    args[1] = NULL;
    args[2] = NULL;

    switch (pid) {
        case -1:    //error
            re = false;
            break;
        case 0:     //child

            if (!redirStderr.empty())
                if (!redifd(redirStderr, 2))
                    exit(EXIT_FAILURE);
            if (!redirStdout.empty())
                if (!redifd(redirStdout, 1))
                    exit(EXIT_SUCCESS);
            extern char **environ;
            //cout << "cmd " << newcmd << endl << "args " << args[0] << args[1] << args[2] << endl ;
            exere = execve("ls", args, environ);
            cout << "execve returned " << exere <<endl;
            exit(EXIT_FAILURE);
            break;
        default:     //perent
            wait(NULL);
            /*pid_t w;
            time_t reff;
            time_t current;

            time(&reff);
            time(&current);
            cout << "pid " << pid << " get pid " << getpid() << endl;
            do {
                //cout << "time elapsed " << difftime(current, reff) << endl;
                time(&current);
                w = waitpid(pid, &status, WNOHANG);
                if (w == -1) {
                  //  perror("waitpid error:");
                    //exit(EXIT_FAILURE);
                }

                //cout << "status of chile: " << WEXITSTATUS(status) << endl;
            } while (difftime(current, reff) <= startTime);*/
            break;
    }
    return re;
}