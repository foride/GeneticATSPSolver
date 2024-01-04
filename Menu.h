#ifndef GENETICATSPSOLVER_MENU_H
#define GENETICATSPSOLVER_MENU_H

#include <iostream>
#include "GeneticAlgorithm.h"

class Menu {

public:
    void startMenu();

private:
    std::vector<std::vector<int>> matrixVector;
    int stopCriterion;
    int initialPopulationSize;
    double mutationRate;
    double crossoverRate;
    int mutationMethod;
};


#endif //GENETICATSPSOLVER_MENU_H
