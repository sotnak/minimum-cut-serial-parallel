//
// Created by antos on 25.09.2021.
//

#include "headers/BBSolver.h"
#include <iostream>
#include <deque>

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

    deque<Configuration> q;

    q.push_back(initConfig);

    Configuration n_config1;
    Configuration n_config2;
    int depth = 0;

    while(!q.empty() && q.size() < (unsigned int)omp_get_num_threads()*32 && depth < currentProblem.nodeCount - 4){
        n_config1 = q.front();
        q.pop_front();

        n_config2 = n_config1;

        depth = n_config1.set1Size + n_config1.set2Size;

        n_config1.assign(depth,1 ,currentProblem.bindingMatrix);
        n_config2.assign(depth,2 ,currentProblem.bindingMatrix);

        q.push_back(n_config1);
        q.push_back(n_config2);
    }

    #pragma omp parallel for default(none) shared(q, currentProblem, currentMinWeight, currentMin, minA, counter, initConfig) num_threads(threadCount)
    for (unsigned int i = 0; i < q.size(); i++){
        rec(q[i],q[i].set1Size + q[i].set2Size);
    }

    q.clear();

    Solution res(currentMin, currentProblem);

    currentMin.clear();

    return res;
}

void BBSolver::rec(const Configuration& config, int depth) {

    #pragma omp atomic update
    counter++;

    int a = config.a();

    if(depth >= currentProblem.nodeCount){

        if(a >= minA) {

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

    if( minA - a > currentProblem.nodeCount - depth ){
        return;
    }

    Configuration n_config1(config);
    n_config1.assign(depth,1,currentProblem.bindingMatrix);

    Configuration n_config2(config);
    n_config2.assign(depth,2,currentProblem.bindingMatrix);


    rec(n_config1, depth + 1);
    rec(n_config2, depth + 1);
}

BBSolver::~BBSolver(){}
