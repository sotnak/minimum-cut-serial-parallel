//
// Created by antos on 24.09.2021.
//

#include "headers/Solution.h"
#include <iostream>

Solution::Solution(const vector<Configuration>& configs, const Problem& problem): problem(problem) {
    configurations = configs;
}

string Solution::toString() {

    string str = to_string(configurations[0].weight) + "\n";

    for(auto config : configurations){
        str += config.toString() + "\n";
    }

    return str;
}

Solution::Solution(const Solution &other): problem(other.problem){
    configurations = other.configurations;
}

Solution::~Solution() {
}

Solution::Solution() = default;