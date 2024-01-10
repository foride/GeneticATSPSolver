#ifndef GENETICATSPSOLVER_PERFORMANCETEST_H
#define GENETICATSPSOLVER_PERFORMANCETEST_H

#include "GeneticAlgorithm.h"
#include <vector>
#include <random>
#include <chrono>
#include <utility>

class PerformanceTest {

public:
    PerformanceTest(std::vector<std::vector<int>> matrix, std::mt19937 rng);
    int performTest(int iterations, int populationSize, double crossoverRate, double mutationRate,
                          double timeLimit, int mutationMethod);


private:
    std::vector<std::vector<int>> graphMatrix;
    std::mt19937 rng;
    std::vector<int> lowestPath;
    int lowestPathValue;

};


#endif //GENETICATSPSOLVER_PERFORMANCETEST_H
