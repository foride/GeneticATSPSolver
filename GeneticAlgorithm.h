#ifndef GENETICATSPSOLVER_GENETICALGORITHM_H
#define GENETICATSPSOLVER_GENETICALGORITHM_H

#include "MatrixATSP.h"
#include <random>

class GeneticAlgorithm
{
private:

    std::vector<std::vector<int>> graph;
    std::vector<std::vector<int>>::size_type graph_size;
    int* localShortestRoute = nullptr;
    int localShortestRouteValue = INT_MAX;
    int startingNode = 0;
    std::mt19937 rng;

    int theShortestRouteValue = 9999;
    std::vector<int> theShortestRoute;


    void initRoute();
    int calculateRouteLength(int * route);
    void setRandomRoute(int * route);
    int gradeRoute(int * route);
    void normalizeGrades(int * grades, int populationSize);
    void copyPopulation(int** from, int** to, int * selectedParents, int populationSize);
    void copyPopulationIntact(int ** from, int ** to, int populationSize);
    void selectByRoulette(int * grades, int * selection, int populationSize);
    void mutate(int * route);
    void swapElements(int * route, int i, int j);
    void crossOnePoint(int * routeA, int * routeB);
    int findInArray(int * array, int number);
    void copyRoute(int * from, int * to);

public:
    explicit GeneticAlgorithm(const std::vector<std::vector<int>>& graph, std::mt19937 rng);
    ~GeneticAlgorithm();

    void printTheShortestRoute();
    int getShortestRouteValue();
    std::vector<int> getShortestRoute();


    void solve(int populationSize, double crossProb, double mutProb, int iterations = -1);
};

#endif //GENETICATSPSOLVER_GENETICALGORITHM_H

