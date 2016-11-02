//
// Created by Stephen ASIEDU on 2016/11/02.
//
#include "../includes/Taskmaster.h"

void    startProcess(vector<string> param, LineEdit *shell){
    if (shell->shutdown){
        write(1, "temp", 4);
        return ;
    }
    if (param.size() < 2){
        write(1, RED, strlen(RED));
        write(1, STARTERR1, strlen(STARTERR1));
        write(1, STARTERR2, strlen(STARTERR2));
        write(1, STARTERR3, strlen(STARTERR3));
        write(1, STARTERR4, strlen(STARTERR4));
        write(1, RESET, strlen(RESET));
        return ;
    }
    if (isAllPresent(param)){
        cout << "starting all" << endl;
    }
    else{
        for(size_t i = 1; i < param.size(); i++){
            cout << time(0) << endl;
            cout << "starting " << param[i].data() << endl;
        }
    }

}
