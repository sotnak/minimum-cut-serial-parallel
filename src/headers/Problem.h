//
// Created by antos on 24.09.2021.
//

#ifndef HW1_PROBLEM_H
#define HW1_PROBLEM_H

#include <sstream>
#include <string>
#include <vector>

using namespace std;


class Problem {
public:
    int nodeCount{};
    uint8_t** bindingMatrix;

    Problem();

    Problem(const Problem& other);

    Problem(int nodeCount, uint8_t** bindingMatrix);

    ~Problem();

    Problem& operator=(const Problem& other);

    string toString() const;

    static Problem ProblemFactory(stringstream& input);
};


#endif //HW1_PROBLEM_H
