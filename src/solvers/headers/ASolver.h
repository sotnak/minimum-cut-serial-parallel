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
    enum Tag {job, result, sizeAndCount, resultValue};
public:
    virtual Solution solve(const Problem& problem) = 0;
    static const char* getName();
    virtual ~ASolver();
    static ASolver* SolverFactory(const string& name);
    [[nodiscard]] long long int getCounter() const;
    void resetCounter();
};


#endif //HW2_ASOLVER_H
