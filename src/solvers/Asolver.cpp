//
// Created by antos on 24.09.2021.
//

#include "headers/ASolver.h"

#include "headers/MasterBBSolver.h"
#include <stdexcept>


ASolver::~ASolver() = default;

ASolver *ASolver::SolverFactory(const string& name){

    if(name == "master")
        return new MasterBBSolver();
    if(name == "slave")
        return new MasterBBSolver();
    else{
        throw invalid_argument("invalid solver name");
    }
}

long long int ASolver::getCounter() const {
    return this->counter;
}

void ASolver::resetCounter() {
    this->counter=0;
}

const char *ASolver::getName() {
    return nullptr;
}
