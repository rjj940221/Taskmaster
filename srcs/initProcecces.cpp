//
// Created by Robert JONES on 2016/11/02.
//

#include <yaml-cpp/node/node.h>
#include <yaml-cpp/yaml.h>
#include "../includes/Taskmaster.h"
#include <string.h>

int matchStpoSignal(string sigIn) {
    if (sigIn.compare("SIGHUP") == 0)
        return SIGHUP;
    if (sigIn.compare("SIGINT") == 0)
        return SIGINT;
    if (sigIn.compare("SIGQUIT") == 0)
        return SIGQUIT;
    if (sigIn.compare("SIGILL") == 0)
        return SIGILL;
    if (sigIn.compare("SIGTRAP") == 0)
        return SIGTRAP;
    if (sigIn.compare("SIGABRT") == 0)
        return SIGABRT;
    if (sigIn.compare("SIGBUS") == 0)
        return SIGBUS;
    if (sigIn.compare("SIGFPE") == 0)
        return SIGFPE;
    if (sigIn.compare("SIGKILL") == 0)
        return SIGKILL;
    if (sigIn.compare("SIGUSR1") == 0)
        return SIGUSR1;
    if (sigIn.compare("SIGSEGV") == 0)
        return SIGSEGV;
    if (sigIn.compare("SIGUSR2") == 0)
        return SIGUSR2;
    if (sigIn.compare("SIGPIPE") == 0)
        return SIGPIPE;
    if (sigIn.compare("SIGALRM") == 0)
        return SIGALRM;
    if (sigIn.compare("SIGTERM") == 0)
        return SIGTERM;
    if (sigIn.compare("SIGCHLD") == 0)
        return SIGCHLD;
    if (sigIn.compare("SIGCONT") == 0)
        return SIGCONT;
    if (sigIn.compare("SIGSTOP") == 0)
        return SIGSTOP;
    if (sigIn.compare("SIGTSTP") == 0)
        return SIGTSTP;
    if (sigIn.compare("SIGTTIN") == 0)
        return SIGTTIN;
    if (sigIn.compare("SIGTTOU") == 0)
        return SIGTTOU;
    if (sigIn.compare("SIGURG") == 0)
        return SIGURG;
    if (sigIn.compare("SIGXCPU") == 0)
        return SIGXCPU;
    if (sigIn.compare("SIGXFSZ") == 0)
        return SIGXFSZ;
    if (sigIn.compare("SIGVTALRM") == 0)
        return SIGVTALRM;
    if (sigIn.compare("SIGPROF") == 0)
        return SIGPROF;
    if (sigIn.compare("SIGWINCH") == 0)
        return SIGWINCH;
    if (sigIn.compare("SIGIO") == 0)
        return SIGIO;
    if (sigIn.compare("SIGSYS") == 0)
        return SIGSYS;
    return -1;
}

Program *build_program(YAML::Node pro) {
    string name;
    string cmd;
    int numProcess;
    string dir;
    bool autostart;
    int startRetries;
    int autorestart;
    int startTime;
    mode_t newUmask;
    int stopSignal;
    int stopTime;
    string redirStdout;
    string redirStderr;
    vector<int> exit_codes;
    map<char *, char *> env;
    try {
        if (pro["name"].IsDefined() && pro["cmd"].IsDefined() && pro["numprocs"] && pro["workingdir"].IsDefined() &&
            pro["autostart"].IsDefined() && pro["autorestart"] && pro["stopsignal"].IsDefined()) {
            name = pro["name"].as<string>();
            cmd = pro["cmd"].as<string>();
            numProcess = pro["numprocs"].as<int>();
            dir = pro["workingdir"].as<string>();
            autostart = pro["autostart"].as<bool>();

            stopSignal = matchStpoSignal(pro["stopsignal"].as<string>());
            if (stopSignal == -1) {
                cout << "signal not recognised" << endl;
                return NULL;
            }

            char *autostartstr = cstring(pro["autorestart"].as<string>());
            if (strcmp(autostartstr, "always") == 0)
                autorestart = ALWAYS;
            else if (strcmp(autostartstr, "never") == 0)
                autorestart = NEVER;
            else if (strcmp(autostartstr, "unexpected") == 0)
                autorestart = UNEXPECTED;
            else {
                delete[] autostartstr;
                return NULL;
            }
            delete[] autostartstr;

        } else {
            recordLogError("Input file", "missing expected peramiter");
            return NULL;
        }
        if (autorestart != NEVER && pro["startretries"].IsDefined())
            startRetries = pro["startretries"].as<int>();
        else {
            if (autorestart != NEVER) {
                recordLogError("Input file", "missing expected data startretries");
                return NULL;
            }
        }

        if (pro["umask"].IsDefined())
            newUmask = pro["umask"].as<int>();

        if (pro["exitcodes"].IsDefined()) {
            YAML::Node exit = pro["exitcodes"];
            for (YAML::const_iterator it = exit.begin(); it != exit.end(); ++it) {
                const YAML::Node &iter = *it;
                exit_codes.push_back(iter.as<int>());
            }
        }

        if (pro["starttime"].IsDefined())
            startTime = pro["starttime"].as<int>();
        else
            startTime = 1;
        //stop signal
        if (pro["stoptime"].IsDefined())
            stopTime = pro["stoptime"].as<int>();
        else
            stopTime = 1;

        if (pro["stdout"].IsDefined())
            redirStdout = pro["stdout"].as<string>();
        if (pro["stderr"].IsDefined())
            redirStderr = pro["stderr"].as<string>();

        if (pro["env"].IsDefined() && pro["env"].IsMap()) {
            YAML::Node envNode = pro["env"];
            for (YAML::const_iterator it = envNode.begin(); it != envNode.end(); ++it) {
                char *key = cstring(it->first.as<string>());       // <- key
                char *val = cstring(it->second.as<string>()); // <- value
                env.insert(pair<char *, char *>(key, val));
                delete[] key;
                delete[] val;
            }
        }
    }
    catch (YAML::Exception exe) {
        //recordLogError("load file", "mismached data type exeption: " + exe.msg );
        return (NULL);
    }
    Program *re;
    re = new Program (name, cmd, numProcess, newUmask, dir, autostart, autorestart, exit_codes, startRetries, startTime,
                      stopSignal, stopTime, redirStdout, redirStderr, env);
    return (re);
}

int checkIfProcecExsists(Program *pro) {
    for (int i = 0; i < processes.size(); ++i) {
        if (processes.at(i).program->getName().compare(pro->getName()) == 0)
            return (i);
    }
    return (-1);
}

bool readFile(string file, bool init) {
    YAML::Node config;
    YAML::Node programs;
    t_Process add;

    try {
        config = YAML::LoadFile(file);
        programs = config["Programs"];
    }
    catch (YAML::Exception exe) {
        recordLogError("load file", "Error opening file");
        return false;
    }
    try {
        int count = 0;

        for (YAML::const_iterator it = programs.begin(); it != programs.end(); ++it) {
            count++;
            const YAML::Node &iter = *it;
            Program *addpro;

            addpro = build_program(iter);
            if (addpro) {
                add.program = addpro;
                add.kill = false;
                add.numRetry = 0;
                add.pid = 0;
                add.state = NOSTART;

                int programindex = checkIfProcecExsists(addpro);
                if (programindex == -1) {
                    if (addpro->getAutostart()) {
                        add.pid = addpro->startProcess();
                        add.state = STARTING;
                        time(&add.reffStart);
                    }
                    processes.push_back(add);
                } else {
                    if (!init) {
                        delete processes.at(programindex).program;
                        processes.at(programindex).program = addpro;
                    } else {
                        //recordLogError("load file", "program name allready exsists at index " + programindex);
                    }
                }
            } else
                ;
                //recordLogError("load file","failed to build program at index " + count);
        }
    }
    catch (YAML::Exception exe) {
        recordLogError("load file","Error extracting data");
        return false;
    }
    return true;
}