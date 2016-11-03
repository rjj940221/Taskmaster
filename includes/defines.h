//
// Created by Stephen ASIEDU on 2016/11/01.
//

#ifndef TASKMASTER_DEFINES_H
#define TASKMASTER_DEFINES_H

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */

#define COMMANDS1 "status start stop restart reload shutdown exit quit help"

#define STARTERR1 "Error: start requires a process name\n"
#define STARTERR2 "start <name>\t\tStart a process\n"
#define STARTERR3 "start <name> <name>\tStart multiple processes\n"
#define STARTERR4 "start all\t\tStart all processes\n"

#define STOPERR1 "Error: stop requires a process name\n"
#define STOPERR2 "stop <name>\t\tStop a process\n"
#define STOPERR3 "stop <name> <name>\tStop multiple processes\n"
#define STOPERR4 "stop all\t\tStop all processes\n"

#define RSTARTERR1 "Error: start requires a process name\n"
#define RSTARTERR2 "restart <name>\t\tRestart a process\n"
#define RSTARTERR3 "restart <name> <name>\tRestart multiple processes\n"
#define RSTARTERR4 "restart all\t\tRestart all processes\n"
#define RSTARTERR5 "Note: restart does not reread config files.\n"

#define HELP1 "\ndefault commands (type help <topic>):\n"
#define HELP2 "=====================================\n"
#define HELP3 "restart start  reload  status\n"
#define HELP4 "quit    stop   exit    shutdown\n"
#define HELP5 "help\t\tPrint a list of available actions\n"
#define HELP6 "help <action>\tPrint help for <action>\n"

#define STARTING 0
#define STOPPED 1
#define FATAL 2
#define RUNNING 3
#define BACKOFF 4
#define NOSTART 5
#define DEAD 6

#endif //TASKMASTER_DEFINES_H
