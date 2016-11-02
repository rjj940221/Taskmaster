//
// Created by Stephen ASIEDU on 2016/11/02.
//

#include "../includes/Taskmaster.h"

void    stopProcess(vector<string> param, LineEdit *shell){
    if (shell->shutdown){
        write(1, "temp", 4);
        return ;
    }
    if (param.size() < 2){
        write(1, RED, strlen(RED));
        write(1, STOPERR1, strlen(STOPERR1));
        write(1, STOPERR2, strlen(STOPERR2));
        write(1, STOPERR3, strlen(STOPERR3));
        write(1, STOPERR4, strlen(STOPERR4));
        write(1, RESET, strlen(RESET));
        return ;
    }
    if (isAllPresent(param)){
        cout << "stopping all" << endl;
    }
    else{
        for(size_t i = 1; i < param.size(); i++){
            cout << "stopping " << param[i].data() << endl;
        }
    }
}