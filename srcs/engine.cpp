//
// Created by Stephen ASIEDU on 2016/11/02.
//

#include "../includes/Taskmaster.h"

using namespace std;

void    processInstruction(string line, LineEdit *shell) {
    smatch base_match;
    regex basic_regex("\\S+");
    vector<string> params;

    while (regex_search(line, base_match, basic_regex)) {
        params.push_back(base_match.str());
        line = base_match.suffix();
    }
    if (strcmp((char *) params[0].data(), "start") == 0){
        startProcess(params, shell);
        return;
    }
    if (strcmp((char *) params[0].data(), "stop") == 0){
        stopProcess(params, shell);
        return;
    }
    if (strcmp((char *) params[0].data(), "restart") == 0){
        restartProcess(params, shell);
        return;
    }
    if (strcmp((char *) params[0].data(), "help") == 0){
        helpProcess(params, shell);
        return;
    }
}


bool    isAllPresent(vector<string> param){
    for (size_t i = 1; i < param.size(); i++){
        if (strcmp((char *)param[i].data(), "all") == 0)
            return true;
    }
    return false;
}

int     isProgramExist(const char *progName){
    for (int i = 0; i < processes.size(); i++){
        if (strcmp(progName, processes[i].program.getName().data()) == 0)
            return i;
    }
    return -1;
}