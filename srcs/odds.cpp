//
// Created by Robert JONES on 2016/11/02.
//
#include "../includes/Taskmaster.h"
using namespace std;

void split(const string &s, char delim, vector<string> &elems) {
    stringstream ss;
    ss.str(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
}

vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}

char *cstring(string in) {
    char *out = new char[in.length() + 1];
    strcpy(out, in.c_str());

    return (out);
}

char **split_string(const string &line, char delim) {
    vector<string> splits = split(line, delim);
    char **re;

    if (!(re = (char **) malloc(sizeof(char *) * (splits.size() + 1))))
        return NULL;
    int size = splits.size();
    //cout << "number of elements " << splits.size() << endl;
    for (int i = 0; i < size; ++i) {
        re[i] = cstring(splits.at(i));
    }
    re[size] = NULL;
    return re;
}

bool redifd(string file, int fd) {
    int newfd;
    char *newLoc = cstring(file);
    bool re;

    //cout << "trying to open " << newLoc << endl;
    newfd = open(newLoc, O_RDWR);
    if (newfd < 0) {
        //cout << "it bork" << endl;
        re = false;
    } else {
        if (dup2(fd, newfd) == -1)
            re = false;
        else {
            //cout << "it file open" << endl;
            re = true;
        }
    }
    delete [](newLoc);
    return re;
}