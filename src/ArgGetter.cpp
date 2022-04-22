//
// Created by pavel on 29.10.21.
//

#include "headers/ArgGetter.h"

#include <cstring>
#include <sstream>

using namespace std;

const char *ArgGetter::getSourcePath(int argc, char **argv) {
    for(int i=0; i<argc; i++) {
        if (strcmp(argv[i], "--source") == 0) {
            if (i + 1 >= argc) {
                throw invalid_argument("file not specified");
            }
            return argv[i + 1];
        }
    }

    throw invalid_argument("--source not found");
}

int ArgGetter::getThreadCount(int argc, char **argv) {
    stringstream strstr;

    for(int i=0; i<argc; i++) {
        if (strcmp(argv[i], "--threads") == 0) {
            if (i + 1 >= argc) {
                throw invalid_argument("value of threads count not specified");
            }

            strstr << argv[i + 1];
            int res;
            strstr>>res;
            return res;
        }
    }

    return -1;
}

