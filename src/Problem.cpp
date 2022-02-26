//
// Created by antos on 24.09.2021.
//

#include <iostream>
#include "headers/Problem.h"

Problem::Problem() = default;

string Problem::toString() const {
    string bindingString;

    for(int i=0; i<nodeCount; i++){
        for(int j=0; j<nodeCount; j++){
            bindingString += to_string(bindingMatrix[i][j]) + " ";
        }
        bindingString += "\n";
    }

    return bindingString;
}

Problem Problem::ProblemFactory(stringstream& input) {

    string str;
    getline(input,str);
    int nodeCnt = stoi(str);

    uint8_t** bm;

    bm = new uint8_t*[nodeCnt];

    for(int i=0; i<nodeCnt; i++){
        bm[i] = new uint8_t[nodeCnt];
    }

    for(int i=0; i<nodeCnt; i++){
        for(int j=0; j<nodeCnt; j++){

            str = "";

            while(str.empty() || str == "\n")
                getline(input,str, ' ');

            bm[i][j] = stoi(str);
        }
    }

    Problem p(nodeCnt, bm);

    for(int i=0; i<nodeCnt; i++){
        delete[] bm[i];
    }
    delete[] bm;

    return p;
}

Problem &Problem::operator=(const Problem &other) {
    if(this ==&other){
        return *this;
    }

    if(nodeCount != other.nodeCount){

        for(int i=0; i<nodeCount; i++){
            delete[] bindingMatrix[i];
        }

        delete[] bindingMatrix;

        if(other.nodeCount == 0){
            bindingMatrix = nullptr;
        }
        else{
            bindingMatrix = new uint8_t*[other.nodeCount];

            for(int i=0; i<other.nodeCount; i++){
                bindingMatrix[i] = new uint8_t[other.nodeCount];
            }
        }
        nodeCount = other.nodeCount;
    }

    for(int i=0; i<other.nodeCount; i++){
        for(int j=0; j<other.nodeCount; j++){
            bindingMatrix[i][j] = other.bindingMatrix[i][j];
        }
    }

    return *this;
}

Problem::~Problem() {
    for(int i=0; i<nodeCount; i++){
        delete[] bindingMatrix[i];
    }

    delete[] bindingMatrix;
}

Problem::Problem(const Problem &other): nodeCount(other.nodeCount){

    bindingMatrix = new uint8_t*[other.nodeCount];

    for(int i=0; i<other.nodeCount; i++){
        bindingMatrix[i] = new uint8_t[other.nodeCount];
    }

    for(int i=0; i<other.nodeCount; i++){
        for(int j=0; j<other.nodeCount; j++){
            bindingMatrix[i][j] = other.bindingMatrix[i][j];
        }
    }
}

Problem::Problem(int nodeCount, uint8_t** bindingMatrix) {
    this->nodeCount = nodeCount;

    this->bindingMatrix = new uint8_t*[nodeCount];

    for(int i=0; i<nodeCount; i++){
        this->bindingMatrix[i] = new uint8_t[nodeCount];
    }

    for(int i=0; i<nodeCount; i++){
        for(int j=0; j<nodeCount; j++){
            this->bindingMatrix[i][j] = bindingMatrix[i][j];
        }
    }
}
