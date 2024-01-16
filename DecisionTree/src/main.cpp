//
// Created by clara on 16/01/24.
//

#include <iostream>
#include <map>

#include "decision_tree.h"

float* load_feature_from_file(std::ifstream& features_file, int& music_style) {
    auto* features = new float[1024];
    return features;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {

        fprintf(stderr, "Wrong number of arguments. Usage: decision_tree test_features output \n");

        return -1;

    }
    return 0;
}