//
// Created by antos on 25.09.2021.
//

#include "headers/BBSolver.h"
#include <iostream>

const char *BBSolver::getName() {
    return "bb";
}

Solution BBSolver::solve(const Problem &problem) {
    minA = problem.nodeCount/2;

    currentProblem = problem;

    Configuration tmpConfig(problem.nodeCount);
    tmpConfig.weight = INT32_MAX;

    currentMin.push_back(tmpConfig);

    Configuration initConfig(problem.nodeCount);
    //initConfig.assign(0,1,currentProblem.bindingMatrix);    //set node 0 to 1 to avoid duplicity in solutions

    rec(initConfig, 0);

    Solution res(currentMin, currentProblem);

    currentMin.clear();

    return res;
}

void BBSolver::rec(const Configuration& config, int depth) {
    this->counter++;

    int a = config.a();

    if(depth >= currentProblem.nodeCount){

        if(a >= minA && a <= currentProblem.nodeCount/2) {
        //if(a == currentProblem.nodeCount/2) {


            if(currentProblem.nodeCount%2==0 && a == currentProblem.nodeCount/2 && config.config[0] == 2){ //filtering duplicity
                return;
            }

            if (config.weight < currentMin[0].weight) {
                currentMin.clear();
                currentMin.push_back(config);
            }

            else if (config.weight == currentMin[0].weight) {
                currentMin.push_back(config);
            }
        }
        return;
    }


    if(config.weight > currentMin[0].weight){
        return;
    }

    if( minA - a > currentProblem.nodeCount - depth || a > currentProblem.nodeCount/2){
    //if( a > currentProblem.nodeCount/2){
        return;
    }

    Configuration n_config1(config);
    n_config1.assign(depth,1,currentProblem.bindingMatrix);

    Configuration n_config2(config);
    n_config2.assign(depth,2,currentProblem.bindingMatrix);

    rec(n_config1, depth+1);
    rec(n_config2, depth+1);
}

BBSolver::~BBSolver(){}
