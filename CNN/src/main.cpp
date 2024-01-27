//
// Created by apolline on 16/01/24.
//

// tensorflow lite
#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/model.h"
#include "tensorflow/lite/interpreter.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>

int main(int argc, char** argv) {
    // DATA filenames
    std::string results_labels = "../data/labels.csv";
    std::string results_data = "../data/dataset.csv";

    // Labels map
    std::map<std::string, int> labels_map;
    labels_map["blues"] = 1;
    labels_map["classical"] = 2;
    labels_map["country"] = 3;
    labels_map["disco"] = 4;
    labels_map["hiphop"] = 5;
    labels_map["jazz"] = 6;
    labels_map["metal"] = 7;
    labels_map["pop"] = 8;
    labels_map["reggae"] = 9;
    labels_map["rock"] = 10;

    // Mise en place data :
    std::vector<int> labels;
    std::vector<std::vector<double>> data;
    std::string cell;
    std::ifstream labels_file(results_labels);
    std::ifstream results_data_file(results_data);

    while(std::getline(labels_file, cell, ',')){
        int ind = labels_map[cell];
        labels.push_back(ind);
    }

    for (int i = 0; i < 1000; ++i){
        std::vector<double> data_line;
        for (int j = 0; j < 1024; ++j){
            std::getline(results_data_file, cell, ',');
            data_line.push_back(std::stod(cell));
        }
        std::getline(results_data_file, cell, '\n');
        data.push_back(data_line);
    }

    // Load the model
    std::unique_ptr<tflite::FlatBufferModel> model =
            tflite::FlatBufferModel::BuildFromFile(filename);

// Build the interpreter
    tflite::ops::builtin::BuiltinOpResolver resolver;
    std::unique_ptr<tflite::Interpreter> interpreter;
    tflite::InterpreterBuilder(*model, resolver)(&interpreter);

// Resize input tensors, if desired.
    interpreter->AllocateTensors();

    float* input = interpreter->typed_input_tensor<float>(0);
// Fill `input`.

    interpreter->Invoke();

    float* output = interpreter->typed_output_tensor<float>(0);


    return 0;
}