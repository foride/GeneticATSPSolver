#include "Menu.h"

void Menu::startMenu() {

    std::cout << "Traveling Salesman Problem solved using a genetic algorithm.\nAuthor: Michal Lewandowski #264458\n";
    std::cout << "Program Menu:\n";
    int option = 0;
    do {

        std::cout << "1. Load data from a file\n";
        std::cout << "2. Set the stopping criterion\n";
        std::cout << "3. Set the initial population size\n";
        std::cout << "4. Set the mutation rate\n";
        std::cout << "5. Set the crossover rate\n";
        std::cout << "6. Choose a mutation method (optional)\n";
        std::cout << "7. Run the algorithm\n";
        std::cout << "8. Exit the program\n";
        std::cout << "Select an option: ";
        std::cin >> option;
        std::random_device rd;
        std::mt19937 rng(rd());
        MatrixATSP matrix;

        switch (option) {
            case 1: {
                std::string filename;
                std::cout << "Enter the name of the file with data: ";
                std::cin >> filename;
                matrixVector = matrix.readFile(filename);
                break;
            }
            case 2: {
                std::cout << "Set the stopping criterion: (number of algorithm iterations)\n";
                std::cout << "0 - number of the algorithm iterations\n";
                std::cout << "1 - time limit set in seconds\n";
                std::cin >> stopCriterion;
                if (stopCriterion == 0) {
                    std::cout << "Enter number of the algorithm iterations: ";
                    std::cin >> numberOfIterations;

                } else if (stopCriterion == 1) {
                    std::cout << "Enter time limit in seconds: ";
                    std::cin >> timeLimit;

                } else {
                    std::cout << "Invalid input, enter 0 or 1\n";
                }
                break;
            }
            case 3: {
                std::cout << "Set the initial population size: ";
                std::cin >> initialPopulationSize;
                break;
            }
            case 4: {
                std::cout << "Set the mutation rate: ";
                std::cin >> mutationRate;
                break;
            }
            case 5: {
                std::cout << "Set the crossover rate: ";
                std::cin >> crossoverRate;
                break;
            }
            case 6: {
                std::cout << "Choose a mutation method:\n";
                std::cout << "0 - swap method\n";
                std::cout << "1 - insert method\n";
                std::cin >> mutationMethod;
                if (mutationMethod != 0 && mutationMethod != 1) {
                    std::cout << "Invalid input, enter 0 or 1\n";

                }
                break;
            }
            case 7: {
                if (matrixVector.empty()) {
                    std::cout << "Please load data from a file first (Option 1)\n";
                } else {
                    GeneticAlgorithm ga(matrixVector, rng);

                    if (mutationMethod != 0 && mutationMethod != 1) {
                        std::cout << "Please set a valid mutation method (Option 6)\n";
                    } else if (stopCriterion != 0 && stopCriterion != 1) {
                        std::cout << "Please set a valid stopping criterion (Option 2)\n";
                    } else {
                        ga.solve(initialPopulationSize, crossoverRate, mutationRate,
                                 numberOfIterations, timeLimit,  mutationMethod);
                        ga.printTheShortestRoute();
                        std::cout << "Koszt ścieżki: " << std::to_string(ga.getShortestRouteValue()) << "\n";
                    }
                }
                break;
            }
            case 8: {
                std::cout << "Exiting the program.\n";
                break;
            }

            default: {

                std::cout << "Invalid option. Please try again.\n";
                break;
            }

        }
    } while (option != 8);
}
