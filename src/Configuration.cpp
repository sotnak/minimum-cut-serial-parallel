//
// Created by antos on 24.09.2021.
//

#include "headers/Configuration.h"
#include <iostream>

string Configuration::toString() const {
    string res;

    for(int i = 0; i < nodeCount; i++){
        res += to_string(config[i]) + " ";
    }

    return res.substr(0, res.length()-1);
}

Configuration::Configuration(const Configuration &other){

    weight = other.weight;
    nodeCount = other.nodeCount;

    set1Size = other.set1Size;
    set2Size = other.set2Size;

    config = new uint8_t[nodeCount];

    for(int i = 0; i < nodeCount; i++){
        config[i]=other.config[i];
    }
}

Configuration::~Configuration() {
    delete[] config;
}

Configuration &Configuration::operator=(const Configuration &other) {
    if(this ==&other){
        return *this;
    }

    weight = other.weight;

    set1Size = other.set1Size;
    set2Size = other.set2Size;

    if(nodeCount != other.nodeCount){
        delete[] config;

        if(other.nodeCount == 0){
            config = nullptr;
        }
        else{
            config = new uint8_t[other.nodeCount];
        }
        nodeCount = other.nodeCount;
    }

    for(int i = 0; i < nodeCount; i++){
        config[i]=other.config[i];
    }

    return *this;
}

Configuration::Configuration(int nodeCount) {
    this->nodeCount = nodeCount;
    config = new uint8_t[nodeCount];

    for(int i = 0; i < nodeCount; i++){
        config[i]=0;
    }
}

void Configuration::assign(int node, int set, uint8_t** bindingMatrix) {
    config[node] = set;

    if(set == 1)
        set1Size++;

    if(set == 2)
        set2Size ++;

    uint8_t tmpSet;

    for(int i = 0; i<nodeCount; i++){

        tmpSet = config[i];

        if(tmpSet!=set && tmpSet!=0){
            weight += bindingMatrix[node][i];
        }
    }
}

int Configuration::setSizeMin() const {
    if(set1Size<set2Size)
        return set1Size;

    return set2Size;
}
