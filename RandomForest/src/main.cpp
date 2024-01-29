//
// Created by clara on 16/01/24.
//

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>

#include "random_forest.h"


struct Data {
    int classe = -1;
    float values[1024];
};

Data* load_data_from_file(std::ifstream& data_file) {
    auto* data = new Data;
    std::string line;
    std::getline(data_file, line, ','); // Read the line from the file
    std::cout << "line length: " << line.length() << std::endl; 
    size_t pos = 0;
    std::string delimiter = " ";
    std::string token;
    int i = 0;
    std::cout << "line: " << line << std::endl;

    // Parse the line and store j and values in the data struct
    std::istringstream iss(line);
    iss >> data->classe;
    while (iss >> token) {
        size_t colonPos = token.find(':');
        if (colonPos != std::string::npos) {
            int index = std::stoi(token.substr(0, colonPos));
            float value = std::stof(token.substr(colonPos + 1));
            data->values[index] = value;
        }
    }

    return data;
}

int main(int argc, char* argv[]) {
    // if (argc != 3) {

    //     fprintf(stderr, "Wrong number of arguments. Usage: decision_tree test_features output \n");

    //     return -1;

    // }
    std::ifstream test_features("../test.features");
    Data* data = load_data_from_file(test_features);
    // std::cout << "j: " << data->j << std::endl;
    // std::cout << data->values[0] << std::endl;
    int32_t features_length = 1024;
    std::int32_t j = random_forest_predict(data->values, features_length);
    std::cout << "j: " << j << std::endl;
    std::cout << "pas encore mort"<< std::endl;
    return 0;
};

    

