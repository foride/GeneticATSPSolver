#include "PerformanceTest.h"

PerformanceTest::PerformanceTest(std::vector<std::vector<int>> matrix, std::mt19937 rng): rng(rng) {
    this->graphMatrix = std::move(matrix);
}

long long PerformanceTest::performTest(int iterations, int populationSize, double crossoverRate, double mutationRate) {

    GeneticAlgorithm ga = GeneticAlgorithm(graphMatrix, rng);
    auto start = std::chrono::high_resolution_clock::now();
    ga.solve(populationSize, crossoverRate, mutationRate, iterations);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);


    return duration.count();
}
