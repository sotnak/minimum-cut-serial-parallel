//
// Created by antos on 25.09.2021.
//

#ifndef HW2_BBSOLVER_H
#define HW2_BBSOLVER_H

#include "ASolver.h"


class BBSolver: public ASolver{

    void rec(const Configuration& config, int depth=0);
    Problem currentProblem;
    vector<Configuration> currentMin;
    int currentMinWeight=INT32_MAX;

    int minA=5;

public:
    static const char * getName();
    Solution solve(const Problem &problem) override;
    ~BBSolver();
};


#endif //HW2_BBSOLVER_H
