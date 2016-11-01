#include "../includes/program.h"
#include <yaml-cpp/yaml.h>


int main () {

    vector<int> exit;

    Program pro("vog", "/bin/rm", 1, "/tmp", true, true, exit, 1, 4, 2, "", "");

    pro.startProcess();
    return 0;
}
