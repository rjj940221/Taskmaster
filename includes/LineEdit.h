//
// Created by Stephen ASIEDU on 2016/10/31.
//

#ifndef TASKMASTER_LINEEDIT_H
#define TASKMASTER_LINEEDIT_H

#include <vector>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <term.h>
#include <curses.h>
#include <string>
#include <unistd.h>
#include <sys/ioctl.h>
#include "defines.h"

using namespace std;

class LineEdit {
private:
    vector<string>  history;
    string          line;
    size_t          cursorPos;
    size_t          lineSize; //should not exceed 255
    size_t          historyPos;
    size_t          historySize;
    struct termios  newSettings;
    struct termios  oldSettings;
    string          prompt;
    static int      shellWrite(int c){ return ((int)write(1, &c, 1));}
    void            addToLine(char c);
    void            removeFromLine();
    void            moveLeft();
    void            moveRight();
    void            upHistory();
    void            downHistory();

public:
    LineEdit();
    ~LineEdit();
    bool            shutdown;
    bool            exitTaskmaster;
    void            startShell();
    bool            readCharacter();
    bool            processLine(char *str);
    string          getLine(){ return line; }

};

bool        goodRule(char *rule);

#endif //TASKMASTER_LINEEDIT_H
