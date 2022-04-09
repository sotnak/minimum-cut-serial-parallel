//
// Created by antos on 25.09.2021.
//

#ifndef HW2_BBSOLVER_H
#define HW2_BBSOLVER_H

#include "ASolver.h"
#include <mpi.h>
#include <deque>


class MasterBBSolver: public ASolver{

    Problem currentProblem;
    vector<Configuration> currentMin;
    int currentMinWeight=INT32_MAX;

    int minA=5;

    void fillQueue(std::deque<Configuration> &q) const;
    void processResults(int resultSize, MPI_Status& status);
    void pushArrToCurrentMin(const int *arr, int size);

public:
    static const char * getName();
    Solution solve(const Problem &problem) override;
    ~MasterBBSolver();
};


#endif //HW2_BBSOLVER_H
