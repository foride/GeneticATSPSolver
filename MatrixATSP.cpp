#include "MatrixATSP.h"

#include <algorithm>
#include <sstream>
#include <iterator>

std::vector<std::vector<int>> MatrixATSP::readFile(const std::string& file) {

    std::ifstream fileStream(file);
    if (fileStream.is_open()) {
        std::string line;
        bool isMatrix = false;
        while (std::getline(fileStream, line)) {

            if (line == "EDGE_WEIGHT_SECTION") {
                isMatrix = true;
            }
            if (line.find(delimiter) != std::string::npos) {
                std::string keyword = line.substr(0, line.find(delimiter));
                std::string value = line.substr(line.find(delimiter) + 1, std::string::npos);
                if (keyword == "DIMENSION") {
                    dimension = std::stoi(value);
                }
            }

            if (isMatrix) {
                std::stringstream stream(line);
                int n;
                while (stream >> n) {
                    this->numbers.push_back(n);
                }
            }
        }

        std::vector<std::vector<int>> matrix = write_to_matrix(dimension, dimension, numbers);
        fileStream.close();
        this->graph_matrix = matrix;
        return matrix;
    } else {
        std::cerr << "Failed to open the file: " << file << "\n";
    }
    return {};
}

std::vector<std::vector<int>> MatrixATSP::write_to_matrix(int rows, int columns, std::vector<int> &v) {
    std::vector<std::vector<int>> matrix(columns, std::vector<int>(rows));
    auto iter = v.begin();
    for (int y = 0; y < columns; ++y) {
        for (int x = 0; x < rows; ++x) {
            if (iter != v.end()) {
                matrix[y][x] = *iter;
                iter++;
            } else {

            }
        }
    }
    return matrix;
}

void MatrixATSP::print_graph_from_file() {


    if (!graph_matrix.empty())
    {
        for (auto & i : graph_matrix)
        {
            for (int j = 0; j < graph_matrix.size(); j++)
            {
                std::cout << i[j] << "\t";
            }
            std::cout << "\n";
        }
    } else {
        std::cout << "Graph is empty!\n";
    }
}