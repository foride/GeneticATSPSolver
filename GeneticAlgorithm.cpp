#include "GeneticAlgorithm.h"
#include <vector>
#include <random>

GeneticAlgorithm::GeneticAlgorithm(const std::vector<std::vector<int>>& graph, std::mt19937 rng): rng(rng) {
    this->graph = graph;
    this->graph_size = graph.size();
}

GeneticAlgorithm::~GeneticAlgorithm()
{
    if (localShortestRoute != nullptr) {
        delete[] localShortestRoute;
    }
}

// *********************************************************************************************
// Initializes shortestRoute and shortestRouteValue using greedy approach treating startNode as 0
// *********************************************************************************************
void GeneticAlgorithm::initRoute()
{
    if (localShortestRoute != nullptr) {
        delete localShortestRoute;
    }
    localShortestRoute = new int[graph_size];
    localShortestRoute[0] = startingNode;

    bool* alreadyVisited = new bool[graph_size];
    for (int i = 0; i < graph_size; i++) {
        alreadyVisited[i] = false;
    }
    alreadyVisited[startingNode] = true;

    for (int i = 0; i < graph_size - 1; i++) {
        int min = INT_MAX;
        int chosen = -1;
        for (int j = 0; j < graph_size; j++) {
            if (graph[localShortestRoute[i]][j] < min && !alreadyVisited[j]) {
                min = graph[localShortestRoute[i]][j];
                chosen = j;
            }
        }
        alreadyVisited[chosen] = true;
        localShortestRoute[i + 1] = chosen;
    }

    delete[] alreadyVisited;
    localShortestRouteValue = calculateRouteLength(localShortestRoute);
}

// *********************************************************************************************
// Calculates length of a given route
// *********************************************************************************************
int GeneticAlgorithm::calculateRouteLength(int * route)
{
    int length = 0;
    for (int i = 0; i < graph_size; i++) {
        length += graph[localShortestRoute[route[i]]][route[i + 1 >= graph_size ? 0 : i + 1]];
    }
    return length;
}

// *********************************************************************************************
// Sets random route at given pointer
// *********************************************************************************************
void GeneticAlgorithm::setRandomRoute(int * route)
{
    std::vector<int> possibleCities;
    for (int i = 0; i < graph_size; i++) {
        possibleCities.push_back(i);
    }
    possibleCities.erase(possibleCities.begin() + startingNode);
    route[0] = startingNode;

    for (int i = 1; possibleCities.size() > 0; i++) {
        int randomNum = std::uniform_int_distribution<int>{ 0, static_cast<int>(possibleCities.size() - 1) }(rng);
        route[i] = possibleCities[randomNum];
        possibleCities.erase(possibleCities.begin() + randomNum);
    }
}

// *********************************************************************************************
// Returns grade of a given route -> the higher, the better
// *********************************************************************************************
int GeneticAlgorithm::gradeRoute(int * route)
{
    return localShortestRouteValue - calculateRouteLength(route);
}

// *********************************************************************************************
// Normalize grades to be greater than zero
// *********************************************************************************************
void GeneticAlgorithm::normalizeGrades(int * grades, int populationSize) {
    int min = 0;
    for (int i = 0; i < populationSize; i++) {
        if (grades[i] < min) {
            min = grades[i];
        }
    }
    min *= -1;
    min++;
    for (int i = 0; i < populationSize; i++) {
        grades[i] += min;
    }
}

// *********************************************************************************************
// Copies one population into another based on selected parents
// *********************************************************************************************
void GeneticAlgorithm::copyPopulation(int ** from, int ** to, int * selectedParents, int populationSize)

{
    for (int j = 0; j < populationSize; j++) {
        for (int i = 0; i < graph_size; i++) {
            to[j][i] = from[selectedParents[j]][i];
        }
    }
}

// *********************************************************************************************
// Copies one population into another intact
// *********************************************************************************************
void GeneticAlgorithm::copyPopulationIntact(int ** from, int ** to, int populationSize)

{
    for (int j = 0; j < populationSize; j++) {
        for (int i = 0; i < graph_size; i++) {
            to[j][i] = from[j][i];
        }
    }
}

// *********************************************************************************************
// Selects parents into selection based on roulette method using grades
// *********************************************************************************************
void GeneticAlgorithm::selectByRoulette(int * grades, int * selection, int populationSize)

{
    int gradesSum = 0;
    for (int i = 0; i < populationSize; i++) {
        gradesSum += grades[i];
        grades[i] = gradesSum;
    }
    std::uniform_int_distribution<std::mt19937::result_type> rulDist(1, gradesSum - 1);

    for (int i = 0; i < populationSize; i++) {
        int selected = rulDist(rng);
        for (int j = 0 ; j < populationSize; j++) {
            if (selected - grades[j] < 0) {
                selection[i] = j;
                break;
            }
        }
    }
}

// *********************************************************************************************
// Mutates given route by swapping two different points
// *********************************************************************************************
void GeneticAlgorithm::mutate(int * route)
{
    int pointA = 0;
    int pointB = 0;
    std::uniform_int_distribution<std::mt19937::result_type> popDist(0, graph_size - 1);
    while (pointA == pointB) {
        pointA = popDist(rng);
        pointB = popDist(rng);
    }
    swapElements(route, pointA, pointB);
}

// *********************************************************************************************
// Swaps two elements in an array
// *********************************************************************************************
void GeneticAlgorithm::swapElements(int * route, int i, int j)
{
    int temp = route[i];
    route[i] = route[j];
    route[j] = temp;
}

// *********************************************************************************************
// Crosses two populations w/ one crossing point - PMX: Partially - Mapped Crossover
// *********************************************************************************************
void GeneticAlgorithm::crossOnePoint(int * routeA, int * routeB)
{
    // Create temp routes
    int *tempRouteA = new int[graph_size];
    int *tempRouteB = new int[graph_size];
    copyRoute(routeA, tempRouteA);
    copyRoute(routeB, tempRouteB);

    // Generate crossing point
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, (graph_size - 1));
    int crossingPoint = dist(rng);

    // Cross that based on PMX - Partially - Mapped Crossover
    for (int i = 0; i < crossingPoint; i++) {
        int position = findInArray(routeA, tempRouteB[i]);
        routeA[position] = routeA[i];
        routeA[i] = tempRouteB[i];
    }
    for (int i = 0; i < crossingPoint; i++) {
        int position = findInArray(routeB, tempRouteA[i]);
        routeB[position] = routeB[i];
        routeB[i] = tempRouteA[i];
    }

    delete[] tempRouteA;
    delete[] tempRouteB;
}

// *********************************************************************************************
// Find given number in an array - return its position
// *********************************************************************************************
int GeneticAlgorithm::findInArray(int * array, int number)
{
    for (int i = 0; i < graph_size; i++) {
        if (array[i] == number) {
            return i;
        }
    }
    return -1;
}

// *********************************************************************************************
// Copies one route into another
// *********************************************************************************************
void GeneticAlgorithm::copyRoute(int * from, int * to)
{
    for (int i = 0; i < graph_size; i++) {
        to[i] = from[i];
    }
}

void GeneticAlgorithm::solve(const int populationSize, const double crossProb, const double mutProb, int iterations)
{
    if (graph.empty() || populationSize % 2 == 1) {
        return;
    }
    // Init the shortest route/the shortest route value using greedy approach
    initRoute();

    if (iterations == -1) {
        iterations = graph_size * graph_size * 2;
    }

    // Init population
    int** population;
    population = new int*[populationSize];
    for (int i = 0; i < populationSize; i++) {
        population[i] = new int[graph_size];
        setRandomRoute(population[i]);
    }
    int** newPopulation;
    newPopulation = new int*[populationSize];
    for (int i = 0; i < populationSize; i++) {
        newPopulation[i] = new int[graph_size];
    }
    int * selectedParents = new int[populationSize];

    // Init grades
    int* grades = new int[populationSize];
    for (int j = 0; j < populationSize; j++) {
        grades[j] = gradeRoute(population[j]);
    }
    normalizeGrades(grades, populationSize);

    // set current best solution as best
    int bestGrade = INT_MAX * (-1);
    int bestFromPop;
    for (int i = 0; i < populationSize; i++) {
        if (grades[i] > bestGrade) {
            bestGrade = grades[i];
            bestFromPop = i;
        }
    }
    copyRoute(population[bestFromPop], localShortestRoute);
    localShortestRouteValue = calculateRouteLength(population[bestFromPop]);

    // Distribution for crossing/mutation prob
    std::uniform_real_distribution<double> happeningProb(0.0, 1.0);

    for (int i = 0; i < iterations; i++) {
        // Selecting parents
        selectByRoulette(grades, selectedParents, populationSize);

        // Create new population based on selected parents
        copyPopulation(population, newPopulation, selectedParents, populationSize);

        // Crossing first / Mutating later
        for (int j = 0; j < populationSize/2; j++) {
            if (happeningProb(rng) <= crossProb) {
                crossOnePoint(newPopulation[j * 2], newPopulation[(j * 2) + 1]);
            }
        }
        for (int j = 0; j < populationSize; j++) {
            if (happeningProb(rng) <= mutProb) {
                mutate(newPopulation[j]);
            }
        }

        // Grading new population
        for (int j = 0; j < populationSize; j++) {
            grades[j] = gradeRoute(newPopulation[j]);
        }
        normalizeGrades(grades, populationSize);

        // Copy new population into population
        copyPopulationIntact(newPopulation, population, populationSize);

        // set new best solution if found
        int bestGrade2 = INT_MAX * (-1);
        int bestFromPop2;
        for (int j = 0; j < populationSize; j++) {
            if (grades[j] > bestGrade2) {
                bestGrade2 = grades[j];
                bestFromPop2 = j;
            }
        }
        if (calculateRouteLength(population[bestFromPop2]) < localShortestRouteValue) {
            copyRoute(population[bestFromPop2], localShortestRoute);
            localShortestRouteValue = calculateRouteLength(population[bestFromPop2]);
            std::cout << i << " " << localShortestRouteValue << "\n";
        }
        if (theShortestRouteValue > localShortestRouteValue) {
            theShortestRouteValue = localShortestRouteValue;
            std::vector<int> shortestRouteVector(localShortestRoute, localShortestRoute + graph_size);
            theShortestRoute = shortestRouteVector;
        }
    }


    // Cleanup grades
    delete[] grades;
    // Cleanup population
    for (int i = 0; i < populationSize; i++) {
        delete[] population[i];
    }
    delete[] population;
    for (int i = 0; i < populationSize; i++) {
        delete[] newPopulation[i];
    }
    delete[] newPopulation;
    delete[] selectedParents;
}

int GeneticAlgorithm::getShortestRouteValue() {
    return this->theShortestRouteValue;
}

void GeneticAlgorithm::printTheShortestRoute() {

    for(int i =0; i< graph_size; i++) {
        std::cout << theShortestRoute[i] << " -> ";
    }
    std::cout << theShortestRoute[0] << "\n";
    
}

std::vector<int> GeneticAlgorithm::getShortestRoute() {
    return theShortestRoute;
}
