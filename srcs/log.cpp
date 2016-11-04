
#include "../includes/Taskmaster.h"

void recordLogError(string prog, string issue) {
    time_t now = time(0);
    struct tm tstruct;
    char buf[90];
    char name[300];
    char name1[300];
    char final[1000];
    struct stat info;

    if (stat("TaskmasterLog", &info) != 0) {
        mkdir("TaskmasterLog", 0755);
    } else if (info.st_mode & S_IFDIR) { ;
    } else {
        mkdir("TaskmasterLog", 0755);
    }
    tstruct = *localtime(&taskmasterTime);
    strftime(name1, sizeof(name1), "%A %d %B %Y %X", &tstruct);
    sprintf(name, "TaskmasterLog/%s.log", name1);
    int fd = open(name, O_RDWR | O_APPEND | O_CREAT, 0775);
    if (fd == -1)
        return;
    flock(fd, LOCK_EX);
    tstruct = *localtime(&now);
    bzero(buf, sizeof(char) * 90);
    strftime(buf, sizeof(buf), "%A %d %B %Y %X", &tstruct);
    sprintf(final, RED "%s\t%s  %s\n" RESET, buf, prog.data(), issue.data());
    write(fd, final, strlen(final));
    flock(fd, LOCK_UN);
    close(fd);
}

void recordLogProcess(string prog, string process) {
    time_t now = time(0);
    struct tm tstruct;
    char buf[90];
    char name[300];
    char name1[300];
    char final[1000];
    struct stat info;


    if (stat("TaskmasterLog", &info) != 0) {
        mkdir("TaskmasterLog", 0755);
    } else if (info.st_mode & S_IFDIR) { ;
    } else {
        mkdir("TaskmasterLog", 0755);
    }
    tstruct = *localtime(&taskmasterTime);
    strftime(name, sizeof(name), "%A %d %B %Y %X", &tstruct);
    sprintf(name, "TaskmasterLog/%s.log",name);
    int fd = open(name, O_RDWR | O_APPEND | O_CREAT, 0775);
    if (fd == -1)
        return;
    flock(fd, LOCK_EX);
    tstruct = *localtime(&now);
    bzero(buf, sizeof(char) * 90);
    strftime(buf, sizeof(buf), "%A %d %B %Y %X", &tstruct);
    sprintf(final, BLUE "%s\t%s  %s\n" RESET, buf, prog.data(), process.data());
    write(fd, final, strlen(final));
    flock(fd, LOCK_UN);
    close(fd);
}

