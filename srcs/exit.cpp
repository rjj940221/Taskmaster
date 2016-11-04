#include "../includes/Taskmaster.h"

void exit(){
    for (int i = 0; i < processes.size(); ++i) {
        kill(processes.at(i).pid, SIGKILL);
        delete(processes.at(i).program);
    }
    processes.clear();
}
