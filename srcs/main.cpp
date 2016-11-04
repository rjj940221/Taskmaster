
#include <yaml-cpp/yaml.h>
#include "../includes/Taskmaster.h"

vector<t_Process> processes;
char *g_file;

int main(int ac, char **av) {
    LineEdit shell;
    bool ret;

    if (ac == 2) {
        g_file = av[1];
        readFile(g_file, true);
        allStatus();

        shell.startShell();
        while (!shell.exitTaskmaster) {
            ret = shell.readCharacter();
            controllerCheck();
            if (ret) {
                processInstruction(shell.getLine(), &shell);
                shell.startShell();

            }
        }
        tcsetattr(0, TCSANOW, &shell.oldSettings);
    } else {
        cout << "Please passe a .yaml config flie" << endl;
    }



    return (0);
}
