//
// Created by antos on 25.09.2021.
//

#include "headers/BBSolver.h"
#include <iostream>

const char *BBSolver::getName() {
    return "bb";
}

void BBSolver::setThreadCount(int count) {
    threadCount = count;
}

Solution BBSolver::solve(const Problem &problem) {
    minA = problem.nodeCount/2;

    currentProblem = problem;

    Configuration initConfig(currentProblem.nodeCount);
    initConfig.assign(0,1,currentProblem.bindingMatrix);    //set node 0 to 1 to avoid duplicity in solutions

    #pragma omp parallel default(none) shared(currentProblem, currentMinWeight, currentMin, minA, counter, initConfig) num_threads(threadCount)
    {
        #pragma omp single
        {
            //cout<<"num of threads: "<<omp_get_num_threads()<<endl;

            rec(initConfig, 1);
        }
    }

    Solution res(currentMin, currentProblem);

    currentMin.clear();

    return res;
}

void BBSolver::rec(const Configuration& config, int depth) {

    #pragma omp atomic update
    counter++;

    int a = config.a();

    if(depth >= currentProblem.nodeCount){

        //if(a >= minA && a <= currentProblem.nodeCount/2) {
        if(a >= minA) {

            /*
            if(currentProblem.nodeCount%2==0 && a == currentProblem.nodeCount/2 && config.config[0] == 2){ //filtering duplicity
                return;
            }
            */

            if(config.weight <= currentMinWeight) {
                #pragma omp critical
                {
                    if (config.weight < currentMinWeight) {
                        currentMinWeight = config.weight;
                        currentMin.clear();
                        currentMin.push_back(config);
                    } else if (config.weight == currentMinWeight) {
                        currentMin.push_back(config);
                    }
                }
            }
        }

        return;
    }


    if(config.weight > currentMinWeight){
        return;
    }

    //if( minA - a > currentProblem.nodeCount - depth || a > currentProblem.nodeCount/2){
    if( minA - a > currentProblem.nodeCount - depth ){
        return;
    }

    Configuration n_config1(config);
    n_config1.assign(depth,1,currentProblem.bindingMatrix);

    Configuration n_config2(config);
    n_config2.assign(depth,2,currentProblem.bindingMatrix);

    if(currentProblem.nodeCount - depth > 3) {
        #pragma omp task default(none) firstprivate(depth, n_config1) shared(currentProblem, currentMinWeight, currentMin, minA, counter)
        rec(n_config1, depth + 1);
    }
    else{
        rec(n_config1, depth + 1);
    }

    rec(n_config2, depth+1);
}

BBSolver::~BBSolver(){}
