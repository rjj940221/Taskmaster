#include <yaml-cpp/yaml.h>
#include "../includes/Taskmaster.h"

int main(int ac, char **av) {
    initProcecces(av[1]);
    /*LineEdit shell;
    bool ret;
    map<char *, char *> env;

    env.insert(std::pair<char *, char *>("FOO", "bar"));
    vector<int> exit;
    exit.push_back(0);
    Program pro("ls", "/bin/ls", 1, 022, "./CMakeFiles", true, false, exit, 0, 3, 4, "", "", env);
    pid_t pid = pro.startProcess();

    pid_t   w;
    int     status;
    bool    gotExit = false;
    time_t  reff;
    time_t  current;
    time(&reff);
    time(&current);
    cout << "pid " << pid << " get pid " << getpid() << endl;
    do {
        //cout << "time elapsed " << difftime(current, reff) << endl;
        time(&current);
        w = waitpid(pid, &status, WNOHANG);
        if (w == -1) {
            perror("waitpid error:");
            //exit(EXIT_FAILURE);
        } else if (w != 0) {
            cout << "got exit status of chile: " << WEXITSTATUS(status) << endl;
            gotExit = true;
            pro.checkExitStat(WEXITSTATUS(status));
        }
    } while (difftime(current, reff) <= pro.getStartTime() && gotExit == false);

    shell.startShell();
    while (!shell.exitTaskmaster) {
        ret = shell.readCharacter();
        if (ret) {
            processInstruction(shell.getLine(), &shell);
            shell.startShell();
        }
    }*/
    return (0);
}
