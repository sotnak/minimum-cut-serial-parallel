//
// Created by pavel on 08.04.22.
//

#include "headers/SlaveBBSolver.h"
#include <deque>
#include <iostream>

const char *SlaveBBSolver::getName() {
    return "bb";
}

void SlaveBBSolver::recFromArr(int* task){
    Configuration tmpconf;

    tmpconf = Configuration(currentProblem.nodeCount);
    for(int i=0; i<currentProblem.nodeCount; i++)
        tmpconf.config[i]=(u_int8_t)task[i];
    tmpconf.numOfEdges = task[currentProblem.nodeCount];
    tmpconf.weight = task[currentProblem.nodeCount+1];
    tmpconf.recalculateSetSizes();

    //cout<<"from master: "<<tmpconf.toString()<<" depth: "<< tmpconf.set1Size + tmpconf.set2Size <<endl;

    #pragma omp parallel default(none) shared(currentProblem, currentMinWeight, currentMin, minA, counter, tmpconf)
    {
        #pragma omp single
        rec(tmpconf, tmpconf.set1Size + tmpconf.set2Size);
    }
}

void SlaveBBSolver::sendResult(const Configuration& config) const{

    int* result = new int[currentProblem.nodeCount+2];

    for(int i = 0; i<currentProblem.nodeCount; i++)
        result[i]=config.config[i];

    result[currentProblem.nodeCount] = config.numOfEdges;
    result[currentProblem.nodeCount+1] = config.weight;

    // 1 2 1 1 2 2 ... 2 numOfEdges weight
    MPI_Send(&result[0], currentProblem.nodeCount+2, MPI_INT, 0, Tag::result, MPI_COMM_WORLD);
}

void SlaveBBSolver::sendAllResults(){

    int* resultSize = new int[2];
    resultSize[0] = (int)currentMin.size();
    resultSize[1] = (int)counter;

    MPI_Send(&resultSize[0], 2, MPI_INT, 0, Tag::sizeAndCount, MPI_COMM_WORLD);

    if(resultSize[0]>0){

        MPI_Send(&currentMinWeight, 1, MPI_INT, 0, Tag::resultValue, MPI_COMM_WORLD);

        for(const Configuration& config: currentMin){
            sendResult(config);
        }
    }

    counter = 0;
    currentMin.clear();

    delete[] resultSize;
}

Solution SlaveBBSolver::solve(const Problem &problem) {
    minA = problem.nodeCount/2;
    currentProblem = problem;

    sendAllResults();

    MPI_Status status;
    auto task = new int[currentProblem.nodeCount+2];
    task[0]=0;

    // 1 2 1 1 2 2 ... 2 numOfEdges weight
    MPI_Recv(&task[0], currentProblem.nodeCount + 2, MPI_INT, 0, Tag::job, MPI_COMM_WORLD, &status);

    while(task[0] != 10){

        recFromArr(task);

        sendAllResults();

        // 1 2 1 1 2 2 ... 2 numOfEdges weight
        MPI_Recv(&task[0], currentProblem.nodeCount+2, MPI_INT, 0, Tag::job, MPI_COMM_WORLD, &status);
    }

    delete[] task;
    return {};
}

void SlaveBBSolver::rec(const Configuration& config, int depth) {

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


    if(currentProblem.nodeCount - depth > 3) {
        #pragma omp task default(none) firstprivate(depth, n_config1) shared(currentProblem, currentMinWeight, currentMin, minA, counter)
        rec(n_config1, depth + 1);
    }
    else{
        rec(n_config1, depth + 1);
    }

    rec(n_config2, depth+1);

}

SlaveBBSolver::~SlaveBBSolver(){}
