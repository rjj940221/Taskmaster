#include "../includes/program.h"
#include <yaml-cpp/yaml.h>


int main() {




    map<char*,char*> env;
    env.insert ( std::pair<char*,char*>("FOO","bar") );
    vector<int> exit;
    exit.push_back(0);
    Program pro("ls", "/bin/ls", 1, 022, "./CMakeFiles", true, false, exit, 0, 3, 4, "", "", env);
    pro.startProcess();
    return 0;
}
