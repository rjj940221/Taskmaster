//
// Created by Stephen ASIEDU on 2016/11/02.
//

#include "../includes/Taskmaster.h"

vector<t_Process> processes = *new vector<t_Process>;

int     main(){
    LineEdit    shell;
    bool        ret;
    Program     *test;
    t_Process   tmp;
    vector<int> exit;
    exit.push_back(0);
    map<char*, char*> env;

    test = new Program("test", "/bin/cat", 1, 022, "/tmp", true, ALWAYS, exit, 5, 10, 15, 10, "/tmp/toto", "/tmp/titi", env);
    tmp.state = STARTING;
    tmp.pid = test->startProcess();
    tmp.program = test;
    tmp.numRetry = 0;
    time(&tmp.reffStart);
    tmp.kill = false;
    processes.push_back(tmp);

    shell.startShell();
    while (!shell.exitTaskmaster){
        ret = shell.readCharacter();
        controllerCheck();
        if (ret){
            processInstruction(shell.getLine(), &shell);
            shell.startShell();
        }
    }
    return (0);
}
