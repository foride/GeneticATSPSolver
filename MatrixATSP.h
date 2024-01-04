#ifndef GENETICATSPSOLVER_MATRIXATSP_H
#define GENETICATSPSOLVER_MATRIXATSP_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class MatrixATSP {
public:

    std::vector<std::vector<int>> readFile(const std::string& file);

    void print_graph_from_file();

private:
    const char delimiter = ':';

    std::vector<int> numbers;
    std::string filename;
    int dimension{};
    std::vector<std::vector<int>> graph_matrix;

    static std::vector<std::vector<int>> write_to_matrix(int rows, int columns, std::vector<int> &v);
};

#endif //GENETICATSPSOLVER_MATRIXATSP_H