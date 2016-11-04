
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


    char msg[300];
    sprintf(msg, "trying to open %s", newLoc);
    recordLogProcess("redirection", msg);

    newfd = open(newLoc, O_RDWR | O_CREAT, 0775);

    if (newfd < 0) {
        sprintf(msg, "could not open %s", newLoc);
        recordLogError("redirection", msg);
        re = false;
    } else {
        if (dup2(newfd, fd) == -1) {
            recordLogError("redirection", "replacement of file descriptor failed");
            re = false;
        } else {
            sprintf(msg, "over wrote file descripter to %s", newLoc);
            recordLogProcess("redirection", msg);
            re = true;
        }
    }
    delete[](newLoc);
    return re;
}