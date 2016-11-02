//
// Created by Stephen ASIEDU on 2016/10/31.
//

#include "../includes/program.h"


using namespace std;

void split(const string &s, char delim, vector<string> &elems) {
    stringstream ss;
    ss.str(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
}

vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}

char *cstring(string in) {
    char *out = new char[in.length() + 1];
    strcpy(out, in.c_str());

    return (out);
}

char **split_string(const string &line, char delim) {
    vector<string> splits = split(line, delim);
    char **re;

    if (!(re = (char **) malloc(sizeof(char *) * (splits.size() + 1))))
        return NULL;
    int size = splits.size();
    cout << "number of elements " << splits.size() << endl;
    for (int i = 0; i < size; ++i) {
        re[i] = cstring(splits.at(i));
    }
    re[size] = NULL;
    return re;
}

bool redifd(string file, int fd) {
    int newfd;
    char *newLoc = cstring(file);
    bool re;

    cout << "trying to open " << newLoc << endl;
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
    delete [](newLoc);
    return re;
}

bool changeWorkingDir(string dir){
    struct stat info;
    char *newLoc = cstring(dir);
    if (stat(newLoc, &info) != 0) {
        printf("cannot access %s\n", newLoc);
        return false;
    }
    else if (info.st_mode & S_IFDIR) {// S_ISDIR() doesn't exist on my windows
        printf("%s is a directory\n", newLoc);
        int re = chdir(newLoc);
        // cout << "chdir returned " << re << endl;
        if (re == 0)
            return true;

    }
    return false;
}

Program::Program(string name, string cmd, int numProcess, int umask, string dir, bool autostart, int autorestart,
                 vector<int> exit_codes, int startRetries, int startTime, int stopTime, string redirStdout,
                 string redirStderr, map<char*, char*> env) {
    this->name = name;
    this->cmd = cmd;
    this->numProcess = numProcess;
    this->numProcessesRunning = 0;
    this->newUmask = umask;
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
        umask(newUmask);
        if (!redirStderr.empty())
            if (!redifd(redirStderr, 2)) {
                cout <<"redir std err faild" << endl;
                exit(EXIT_FAILURE);
            }
        if (!redirStdout.empty())
            if (!redifd(redirStdout, 1)){
                cout <<"redir std out faild tryed to re dit to |"<< redirStdout<<"|" << endl;
                exit(EXIT_FAILURE);
            }
        if (!dir.empty())
            if(!changeWorkingDir(dir)){
                cout <<"redir working dir faild" << endl;
                exit(EXIT_FAILURE);
            }
        cout << "checking env map"<<endl;
        for (map<char*, char*>::iterator it=env.begin(); it!=env.end(); ++it) {
            setenv(it->first, it->second, 1);
        }
        extern char **environ;
        //cout << "cmd " << newcmd << endl << "args " << args[0] << args[1] << args[2] << endl ;
        exere = execve(args[0], args, environ);
        cout << "execve returned " << exere << endl;
        exit(EXIT_FAILURE);
    } else {  //perent
        //wait(NULL);
        /*pid_t w;
        bool    gotExit = false;
        time_t reff;
        time_t current;
        time(&reff);
        time(&current);
        re = pid;
        cout << "pid " << pid << " get pid " << getpid() << endl;
        do {
            //cout << "time elapsed " << difftime(current, reff) << endl;
            time(&current);
            w = waitpid(pid, &status, WNOHANG);
            if (w == -1) {
                perror("waitpid error:");
                //exit(EXIT_FAILURE);
            }
            else if (w != 0) {
                cout << "got exit status of chile: " << WEXITSTATUS(status) << endl;
                gotExit = true;
                checkExitStat(WEXITSTATUS(status));
            }
        } while (difftime(current, reff) <= startTime && gotExit == false);*/
        delete[] args;
        return pid;
    }
    // delete[] args;
    // return re;
}

bool Program::checkExitStat(int status) {
    for (int i = 0; i < exit_codes.size(); ++i) {
        if (exit_codes.at(i) == status)
            return true;
    }
    return false;
}