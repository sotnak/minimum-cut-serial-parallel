//
// Created by antos on 24.09.2021.
//

#ifndef HW2_SOLUTION_H
#define HW2_SOLUTION_H

#include <vector>
#include <string>

#include "Problem.h"
#include "Configuration.h"

using namespace std;


class Solution {
public:
    vector<Configuration> configurations;
    Problem problem;

    Solution(const vector<Configuration>& configs, const Problem& problem);

    Solution();
    Solution(const Solution& other);

    ~Solution();

    string toString();
};


#endif //HW2_SOLUTION_H
