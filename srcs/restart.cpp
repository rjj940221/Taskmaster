//
// Created by Stephen ASIEDU on 2016/11/02.
//

#include "../includes/Taskmaster.h"

void    restartProcess(vector<string> param, LineEdit *shell){
    if (shell->shutdown){
        write(1, "temp", 4);
        return ;
    }
    if (param.size() < 2){
        write(1, RED, strlen(RED));
        write(1, RSTARTERR1, strlen(RSTARTERR1));
        write(1, RSTARTERR2, strlen(RSTARTERR2));
        write(1, RSTARTERR3, strlen(RSTARTERR3));
        write(1, RSTARTERR4, strlen(RSTARTERR4));
        write(1, RSTARTERR5, strlen(RSTARTERR5));
        write(1, RESET, strlen(RESET));
        return ;
    }
    if (isAllPresent(param)){
        cout << "restarting all" << endl;
    }
    else{
        for(size_t i = 1; i < param.size(); i++){
            cout << "restarting " << param[i].data() << endl;
        }
    }
}