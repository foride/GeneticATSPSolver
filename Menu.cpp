#include "Menu.h"

void Menu::startMenu() {

    std::cout << "Traveling Salesman Problem solved using a genetic algorithm.\nAuthor: Michal Lewandowski #264458\n";
    std::cout << "Program Menu:\n";
    int option;
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
                std::cout << "Set the stopping criterion: (number of algorithm iterations)";
                std::cin >> stopCriterion;
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
                std::cout << "Choose a mutation method (1, 2, 3, etc.): ";
                std::cin >> mutationMethod;
                break;
            }
            case 7: {
                GeneticAlgorithm ga(matrixVector, rng);
                // To finish - needs mutation method and stop criterion
                ga.solve(initialPopulationSize, crossoverRate, mutationRate, stopCriterion);
                ga.printTheShortestRoute();
                std::cout << std::to_string(ga.getShortestRouteValue()) << "\n";
            }
            case 8:
                std::cout << "Exiting the program.\n";
                break;
            default:
                std::cout << "Invalid option. Please try again.\n";
                break;
        }
    } while (option != 8);
}
