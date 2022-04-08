//
// Created by antos on 25.09.2021.
//

#include "headers/MasterBBSolver.h"
#include <iostream>
#include <deque>

const char *MasterBBSolver::getName() {
    return "bb";
}

void MasterBBSolver::fillQueue(deque<Configuration>& q) const{
    Configuration initConfig(currentProblem.nodeCount);
    initConfig.assign(0,1,currentProblem.bindingMatrix);    //set node 0 to 1 to avoid duplicity in solutions

    q.push_back(initConfig);

    Configuration n_config1;
    Configuration n_config2;
    int depth = 0;
    int world_size;

    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    while(!q.empty() && q.size() < (unsigned int)world_size*32 && depth < currentProblem.nodeCount - 4){
        n_config1 = q.front();
        q.pop_front();

        n_config2 = n_config1;

        depth = n_config1.set1Size + n_config1.set2Size;

        n_config1.assign(depth,1 ,currentProblem.bindingMatrix);
        n_config2.assign(depth,2 ,currentProblem.bindingMatrix);

        q.push_back(n_config1);
        q.push_back(n_config2);
    }
}

void MasterBBSolver::processResults(int numOfResults, MPI_Status& status){

    int resultValue = INT32_MAX;
    int** results;
    Configuration tmpconf;

    MPI_Recv(&resultValue, 1, MPI_INT, status.MPI_SOURCE, Tag::resultValue, MPI_COMM_WORLD, &status);

    results = new int*[numOfResults];

    for(int i=0; i<numOfResults; i++){
        results[i] = new int[currentProblem.nodeCount + 2];
    }

    // 1 2 1 1 2 2 ... 2 numOfEdges weight
    MPI_Recv(&results[0][0], numOfResults*(currentProblem.nodeCount+2), MPI_INT, status.MPI_SOURCE, Tag::result, MPI_COMM_WORLD, &status);

    if(resultValue<=currentMinWeight){

        if(resultValue<currentMinWeight){
            currentMinWeight = resultValue;
            currentMin.clear();
        }

        for(int i = 0; i<numOfResults; i++){
            cout<<"m: ";
            for(int j = 0; j<currentProblem.nodeCount; j++){
                cout << results[i][j] << " ";
            }
            cout << results[i][currentProblem.nodeCount] <<" ";
            cout << results[i][currentProblem.nodeCount+1]<< endl;
        } cout << endl;

        for(int i=0; i<numOfResults; i++){
            tmpconf = Configuration(currentProblem.nodeCount);
            for(int j=0; j<currentProblem.nodeCount; j++)
                tmpconf.config[j]=results[i][j];
            tmpconf.numOfEdges = results[i][currentProblem.nodeCount];
            tmpconf.weight = results[i][currentProblem.nodeCount+1];
            tmpconf.recalculateSetSizes();

            //cout<<"from slave: "<<tmpconf.toString()<<endl;

            currentMin.push_back(tmpconf);
        }

    }

    /*for(int i=0; i<numOfResults; i++){
        delete[] results[i];
    }*/

    delete[] results;
}

Solution MasterBBSolver::solve(const Problem &problem) {
    currentProblem = problem;
    deque<Configuration> q;

    fillQueue(q);

    MPI_Status status;
    int* resultSize = new int[2];   // numOfResults iterationsCount
    Configuration tmpconf;
    auto task = new int[currentProblem.nodeCount+2];

    while(!q.empty()){
        MPI_Recv(&resultSize[0], 2, MPI_INT, MPI_ANY_SOURCE, Tag::sizeAndCount, MPI_COMM_WORLD, &status);
        //cout<<"from slave: \n\tnumOfResults: "<< resultSize[0] << " \n\titerationsCount: "<< resultSize[1] << endl;

        counter += resultSize[1];

        if(resultSize[0]>0){
            processResults(resultSize[0], status);
        }

        tmpconf = q.front();
        q.pop_front();

        for(int i=0; i<currentProblem.nodeCount; i++){
            task[i] = tmpconf.config[i];
        }

        task[currentProblem.nodeCount] = tmpconf.numOfEdges;
        task[currentProblem.nodeCount+1] = tmpconf.weight;

        // 1 2 1 1 2 2 ... 2 numOfEdges weight
        MPI_Send(&task[0], currentProblem.nodeCount+2, MPI_INT, status.MPI_SOURCE, Tag::job, MPI_COMM_WORLD);
    }

    int world_size;

    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    for(int i=0; i<world_size-1; i++) {
        MPI_Recv(&resultSize[0], 2, MPI_INT, MPI_ANY_SOURCE, Tag::sizeAndCount, MPI_COMM_WORLD, &status);

        counter += resultSize[1];

        if (resultSize[0] > 0) {
            processResults(resultSize[0], status);
        }

        for (int j = 0; j < currentProblem.nodeCount + 1; j++) {
            task[j] = 10;
        }

        MPI_Send(&task[0], currentProblem.nodeCount+1, MPI_INT, status.MPI_SOURCE, Tag::job, MPI_COMM_WORLD);
    }
    delete[] task;
    delete[] resultSize;

    Solution res(currentMin, currentProblem);

    currentMin.clear();

    return res;
}

MasterBBSolver::~MasterBBSolver(){}
