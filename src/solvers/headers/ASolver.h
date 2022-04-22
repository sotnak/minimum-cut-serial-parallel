//
// Created by antos on 24.09.2021.
//

#ifndef HW2_ASOLVER_H
#define HW2_ASOLVER_H

#include "../../headers/Problem.h"
#include "../../headers/Solution.h"


class ASolver {
protected:
    long long int counter=0;
public:
    virtual Solution solve(const Problem& problem) = 0;
    static const char* getName();
    virtual ~ASolver();
    static ASolver* SolverFactory();
    [[nodiscard]] long long int getCounter() const;
    void resetCounter();

    virtual void setThreadCount(int count);
};


#endif //HW2_ASOLVER_H
