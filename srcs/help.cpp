#include "../includes/Taskmaster.h"

void    helpProcess(vector<string> param, LineEdit *shell){
    if (shell->shutdown){
        write(1, "temp", 4);
        return ;
    }
    if (param.size() < 2){
        write(1, BLUE, strlen(BLUE));
        write(1, HELP1, strlen(HELP1));
        write(1, HELP2, strlen(HELP2));
        write(1, HELP3, strlen(HELP3));
        write(1, HELP4, strlen(HELP4));
        write(1, RESET, strlen(RESET));
        write(1, "\n", 1);
        return ;
    }
    if (strcmp((char *) param[1].data(), "start") == 0){
        write(1, BLUE, strlen(BLUE));
        write(1, STARTERR2, strlen(STARTERR2));
        write(1, STARTERR3, strlen(STARTERR3));
        write(1, STARTERR4, strlen(STARTERR4));
        write(1, RESET, strlen(RESET));
        return ;
    }
    if (strcmp((char *) param[1].data(), "stop") == 0){
        write(1, BLUE, strlen(BLUE));
        write(1, STOPERR2, strlen(STOPERR2));
        write(1, STOPERR3, strlen(STOPERR3));
        write(1, STOPERR4, strlen(STOPERR4));
        write(1, RESET, strlen(RESET));
        return ;
    }
    if (strcmp((char *) param[1].data(), "restart") == 0){
        write(1, BLUE, strlen(BLUE));
        write(1, RSTARTERR2, strlen(RSTARTERR2));
        write(1, RSTARTERR3, strlen(RSTARTERR3));
        write(1, RSTARTERR4, strlen(RSTARTERR4));
        write(1, RSTARTERR5, strlen(RSTARTERR5));
        write(1, RESET, strlen(RESET));
        return ;
    }
    if (strcmp((char *) param[1].data(), "help") == 0){
        write(1, BLUE, strlen(BLUE));
        write(1, HELP5, strlen(HELP5));
        write(1, HELP6, strlen(HELP6));
        write(1, RESET, strlen(RESET));
        return ;
    }
    if (strcmp((char *) param[1].data(), "reload") == 0){
        write(1, BLUE, strlen(BLUE));
        write(1, RELOAD1, strlen(RELOAD1));
        write(1, RESET, strlen(RESET));
        return ;
    }
    if (strcmp((char *) param[1].data(), "shutdown") == 0){
        write(1, BLUE, strlen(BLUE));
        write(1, SHUTDOWN, strlen(SHUTDOWN));
        write(1, RESET, strlen(RESET));
        return ;
    }
    write(1, RED, strlen(RED));
    write(1, "*** No help on ", 15);
    write(1, (char *)param[1].data(), strlen((char *)param[1].data()));
    write(1, "\n", 1);
    write(1, RESET, strlen(RESET));
}