//
// Created by antos on 24.09.2021.
//

#ifndef HW2_CONFIGURATION_H
#define HW2_CONFIGURATION_H

#include <vector>
#include <utility>
#include <cstdint>
#include <string>

using namespace std;


class Configuration {
public:
    uint8_t* config = new uint8_t[1];
    int nodeCount = 0;
    int weight = 0;

    int set1Size = 0;
    int set2Size = 0;

    int numOfEdges = 0;

    Configuration(int nodeCount);
    Configuration(const Configuration& configuration);
    Configuration() = default;

    ~Configuration();

    Configuration& operator=(const Configuration& other);

    [[nodiscard]] string toString() const;

    void assign(int node, int set, uint8_t** bindingMatrix);

    int a() const;
};


#endif //HW2_CONFIGURATION_H
