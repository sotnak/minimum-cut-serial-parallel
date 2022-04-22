//
// Created by antos on 25.09.2021.
//

#ifndef HW2_BBSOLVER_H
#define HW2_BBSOLVER_H

#include "ASolver.h"
#include <omp.h>


class BBSolver: public ASolver{

    void rec(const Configuration& config, int depth=0);
    Problem currentProblem;
    vector<Configuration> currentMin;
    int currentMinWeight=INT32_MAX;
    int threadCount = omp_get_max_threads();

    int minA=5;

public:
    static const char * getName();
    Solution solve(const Problem &problem) override;
    ~BBSolver();

    void setThreadCount(int count);
};


#endif //HW2_BBSOLVER_H
