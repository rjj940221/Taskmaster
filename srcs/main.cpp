#include "../includes/Taskmaster.h"

int     main(){
    LineEdit    shell;
    bool        ret;

    shell.startShell();
    while (!shell.exitTaskmaster){
        ret = shell.readCharacter();
        if (ret){
            processInstruction(shell.getLine(), &shell);
            shell.startShell();
        }
    }
    return (0);
}