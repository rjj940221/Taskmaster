//
// Created by Stephen ASIEDU on 2016/11/03.
//

#include "../includes/Taskmaster.h"

void    recordLogError(string prog, string issue){
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[90];
    int fd = open("taskmaster.log", O_RDWR | O_APPEND | O_CREAT | 0755);

    if (fd == -1)
        return ;
    tstruct = *localtime(&now);
    bzero(buf, sizeof(char) * 90);
    buf[0] = '[';
    strftime(&buf[0], sizeof(buf) - 1, "%A %d %B %Y %X", &tstruct);
    buf[strlen(buf)] = ']';
    buf[strlen(buf) + 1] = '\t';
    write(fd, RED, strlen(RED));
    write(fd, buf, strlen(buf));
    write(fd, prog.data(), prog.size());
    write(fd, "  ", 2);
    write(fd, issue.data(), issue.size());
    write(fd, "\n", 1);
    write(1, RESET, strlen(RESET));
}

void    recordLogProcess(string prog, string process){
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[90];
    int fd = open("taskmaster.log", O_RDWR | O_APPEND | O_CREAT | 0755);

    if (fd == -1)
        return ;
    tstruct = *localtime(&now);
    bzero(buf, sizeof(char) * 90);
    buf[0] = '[';
    strftime(&buf[0], sizeof(buf) - 1, "%A %d %B %Y %X", &tstruct);
    buf[strlen(buf)] = ']';
    buf[strlen(buf) + 1] = '\t';
    write(fd, buf, strlen(buf));
    write(fd, prog.data(), prog.size());
    write(fd, "  ", 2);
    write(fd, process.data(), process.size());
    write(fd, "\n", 1);
}

