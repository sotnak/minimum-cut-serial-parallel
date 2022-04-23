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

const char *ArgGetter::getOutputPath(int argc, char **argv) {
    for(int i=0; i<argc; i++) {
        if (strcmp(argv[i], "--out") == 0) {
            if (i + 1 >= argc) {
                throw invalid_argument("file not specified");
            }
            return argv[i + 1];
        }
    }

    throw invalid_argument("--out not found");
}
