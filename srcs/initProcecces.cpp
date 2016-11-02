//
// Created by Robert JONES on 2016/11/02.
//

#include <yaml-cpp/node/node.h>
#include <yaml-cpp/yaml.h>
#include "../includes/Taskmaster.h"
#include <string.h>

Program *build_program(YAML::Node pro) {
    if (pro["name"].IsDefined() && pro["cmd"].IsDefined() && pro["numprocs"] && pro["workingdir"] && pro["autostart"]
            && pro["autorestart"] && pro["startretries"] && )
        string name = pro["name"].as<string>();
    else
        return NULL;

    string cmd = pro["cmd"].as<string>();
    int numProcess = pro["numprocs"].as<int>();
    mode_t newUmask = pro["umask"].as<int>();
    string dir = pro["workingdir"].as<string>();
    bool autostart = pro["autostart"].as<bool>();

    int autorestart;
    char *autostartstr = cstring(pro["autorestart"].as<string>());
    if (strcmp(autostartstr, "always") == 0)
        autorestart = 1;
    else if (strcmp(autostartstr, "never") == 0)
        autorestart = 2;
    else if (strcmp(autostartstr, "unexpected") == 0)
        autorestart = 3;
    else {
        delete [] autostartstr;
        return NULL;
    }
    delete [] autostartstr;

    vector<int> exit_codes;
    YAML::Node exit = pro["exitcodes"];
    for (YAML::const_iterator it = exit.begin(); it != exit.end(); ++it) {
        const YAML::Node &iter = *it;
        exit_codes.push_back(iter.as<int>());
    }

    int startRetries = pro["startretries"].as<int>();
    int startTime = pro["starttime"].as<int>();
    //stop signal
    int stopTime = pro["stoptime"].as<int>();
    string redirStdout = pro["stdout"].as<string>();
    string redirStderr = pro["stderr"].as<string>();

    map<char *, char *> env;
    YAML::Node envNode = pro["env"];
    for (YAML::const_iterator it = envNode.begin(); it != envNode.end(); ++it) {
        char *key = cstring(it->first.as<string>());       // <- key
        char *val = cstring(it->second.as<string>()); // <- value
        env.insert(pair<char *, char *>(key, val));
        delete[] key;
        delete[] val;
    }
    return NULL;
}

void initProcecces(string file) {
    YAML::Node config = YAML::LoadFile(file);
    YAML::Node programs = config["Programs"];

    for (YAML::const_iterator it = programs.begin(); it != programs.end(); ++it) {
        /*std::string key = it->first.as<std::string>();       // <- key
        cTypeList.push_back(it->second.as<CharacterType>()); // <- value*/
        const YAML::Node &iter = *it;


        build_program(iter);
    }
}
