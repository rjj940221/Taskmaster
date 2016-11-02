//
// Created by Stephen ASIEDU on 2016/10/31.
//

#include "../includes/LineEdit.h"

LineEdit::LineEdit() {
    this->cursorPos = 0;
    this->historySize = 0;
    this->historyPos = 0;
    this->lineSize = 0;
    this->line = "";
    this->exitTaskmaster = false;
    this->prompt = "Taskmaster> ";
    this->shutdown = false;
    //cout << "lineEdit constructed" << endl;
}

LineEdit::~LineEdit() {
    //cout << "LineEdit destructed" << endl;
}

void        LineEdit::startShell() {
    char rule[] = {'s', 'c'};

    tcgetattr(0, &this->oldSettings);
    tcgetattr(0, &this->newSettings);
    this->newSettings.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW, &this->newSettings);
    write(1, GREEN, strlen(GREEN));
    write(1, this->prompt.data(), this->prompt.length());
    write(1, RESET, strlen(RESET));
    tgetent(0, getenv("TERM"));
    tputs(tgetstr(rule, 0), 0, this->shellWrite);
    this->cursorPos = 0;
    this->historySize = 0;
    this->historyPos = 0;
    this->lineSize = 0;
    this->line = "";
}

void        LineEdit::addToLine(char c) {
    char    modeIn[] = {'i', 'm'}; //enter insert mode
    char    modeOut[] = {'e', 'i'}; //leave insert mode

    this->line.insert(this->cursorPos, 1, c);
    this->cursorPos++;
    tputs(tgetstr(modeIn, 0), 0, this->shellWrite);
    write(1, &c, 1);
    tputs(tgetstr(modeOut, 0), 0, this->shellWrite);
}

void        LineEdit::removeFromLine() {
    char    del[] = {'d', 'c'};
    char    move[] = {'l', 'e'};

    if (this->cursorPos < 1)
        return ;
    this->line.erase(this->cursorPos - 1, 1);
    this->cursorPos--;
    tputs(tgetstr(move, 0), 0, this->shellWrite);
    tputs(tgetstr(del, 0), 0, this->shellWrite);
}

bool        LineEdit::processLine(char *str) {
    if (strcmp(str, "exit") == 0 || strcmp(str, "quit") == 0){
        this->exitTaskmaster = true;
        write(1, GREEN, strlen(GREEN));
        write(1, "Taskmaster exited\n", 18);
        write(1, RESET, strlen(RESET));
    }else if (strlen(str) < 1) {
        this->startShell();
    }
    else if (!goodRule(str)){
        write(1, RED, strlen(RED));
        write(1, "*** Unknown syntax: ", 20);
        write(1, str, strlen(str));
        write(1, RESET, strlen(RESET));
        write(1, "\n", 1);
        this->startShell();
    }
    else
        return true;
    return false;
}

bool        LineEdit::readCharacter() {
    ssize_t  ret = 0;
    char    buf[4];

    bzero(buf, 4);
    ret = read(0, buf, 4);
    if (ret == 1){
        if (buf[0] == 127)
            this->removeFromLine();
        else if(buf[0] == 10){
            write(1, "\n", 1);
            return (this->processLine((char *)this->line.data()));
        }
        else
            this->addToLine(buf[0]);
    }
    return false;
}

bool        goodRule(char *rule){
    if (strncmp(rule, "start", 5) == 0 && (rule[5] == ' ' || rule[5] == '\0'))
        return true;
    if (strncmp(rule, "stop", 4) == 0 && (rule[4] == ' ' || rule[4] == '\0'))
        return true;
    if (strncmp(rule, "status", 6) == 0 && (rule[6] == ' ' || rule[6] == '\0'))
        return true;
    if (strncmp(rule, "restart", 7) == 0 && (rule[7] == ' ' || rule[7] == '\0'))
        return true;
    if (strncmp(rule, "reload", 6) == 0 && (rule[6] == ' ' || rule[6] == '\0'))
        return true;
    if (strncmp(rule, "shutdown", 8) == 0 && (rule[8] == ' ' || rule[8] == '\0'))
        return true;
    if (strncmp(rule, "help", 4) == 0 && (rule[4] == ' ' || rule[4] == '\0'))
        return true;
    if (strncmp(rule, "exit", 4) == 0 && (rule[4] == ' ' || rule[4] == '\0'))
        return true;
    if (strncmp(rule, "quit", 4) == 0 && (rule[4] == ' ' || rule[4] == '\0'))
        return true;
    return false;
}