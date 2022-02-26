//
// Created by antos on 24.09.2021.
//

#include "headers/ASolver.h"

#include "headers/BBSolver.h"
#include <stdexcept>


ASolver::~ASolver() = default;

ASolver *ASolver::SolverFactory(){

    return new BBSolver();
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
