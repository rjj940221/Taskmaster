#include <yaml-cpp/yaml.h>
#include "../includes/Taskmaster.h"

vector<t_Process> processes;

int     main(int ac, char **av){
   LineEdit    shell;
    bool        ret;

    if (ac == 2) {
        readFile(av[1], true);

        shell.startShell();
        while (!shell.exitTaskmaster){
            ret = shell.readCharacter();
            controllerCheck();
            if (ret){
                processInstruction(shell.getLine(), &shell);
                shell.startShell();
            }
        }
    }else{
        cout << "Please passe a config.yaml" << endl;
    }   //controllerCheck();
        return (0);
}
