
#ifndef TASKMASTER_ODDS_H
#define TASKMASTER_ODDS_H

#include <string>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

void split(const string &s, char delim, vector<string> &elems);

vector<string> split(const string &s, char delim);

char *cstring(string in);

char **split_string(const string &line, char delim);

bool redifd(string file, int fd);

#endif //TASKMASTER_ODDS_H
