//
// Created by pavel on 08.04.22.
//

#ifndef PDP_SLAVEBBSOLVER_H
#define PDP_SLAVEBBSOLVER_H


#include "ASolver.h"
#include <mpi.h>

class SlaveBBSolver: public ASolver{

    void rec(const Configuration& config, int depth=0);
    Problem currentProblem;
    vector<Configuration> currentMin;
    int currentMinWeight=INT32_MAX;

    int minA=5;

    void sendAllResults();
    void sendResult(const Configuration& config) const;
    void recFromArr(int *task);

public:
    static const char * getName();
    Solution solve(const Problem &problem) override;
    ~SlaveBBSolver();
};


#endif //PDP_SLAVEBBSOLVER_H
