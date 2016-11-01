#include "Taskmaster.h"

int     main(){
    LineEdit    shell;

    shell.startShell();
    while (!shell.exitTaskmaster){
        shell.readCharacter();
    }
    return (0);
}