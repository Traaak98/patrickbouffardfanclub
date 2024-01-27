//
// Created by apolline on 16/01/24.
//

// tensorflow lite
#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/model.h"
#include "tensorflow/lite/interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/micro/kernels/all_ops_resolver.h"
#include "tensorflow/lite/micro/simple_memory_allocator.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>

std::unique_ptr<tflite::Interpreter> buildAudioClassificationModel();
void build_vectors_data(std::vector<int> &labels, std::vector<std::vector<double>> &data, std::string results_labels, std::string results_data, std::map<std::string, int> labels_map );

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

    // Build vectors data
    std::vector<int> labels;
    std::vector<std::vector<double>> data;
    build_vectors_data(labels, data, results_labels, results_data, labels_map);

    // Construire le modèle CNN
    auto interpreter = buildAudioClassificationModel();

// Copiez les données audio dans le tenseur d'entrée du modèle
    float *inputTensor = interpreter->typed_input_tensor<float>(0);

    for (size_t i = 0; i < data.size(); ++i) {
        for (size_t j = 0; j < data[i].size(); ++j) {
            inputTensor[i * data[i].size() + j] = static_cast<float>(data[i][j]);
        }
    }

    // Effectuer l'inférence
    interpreter->Invoke();

    // Récupérer les résultats de l'inférence
    float *outputTensor = interpreter->typed_output_tensor<float>(0);

    // Afficher les résultats (à adapter selon le format de sortie de votre modèle)
    for (int i = 0; i < interpreter->outputs()[0] -> bytes / sizeof(float); i++) {
        std::cout << "Classe " << i << ": " << outputTensor[i] << std::endl;
    }

    return 0;
}

void build_vectors_data(std::vector<int> &labels, std::vector<std::vector<double>> &data, std::string results_labels, std::string results_data, std::map<std::string, int> labels_map ){
    // Mise en place data :
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
}


std::unique_ptr<tflite::Interpreter> buildAudioClassificationModel() {
    tflite::MicroMutableOpResolver<10> resolver;
    resolver.AddConv2D();
    resolver.AddMaxPool2D();
    resolver.AddFullyConnected();
    resolver.AddSoftmax();
    resolver.AddReshape();
    resolver.AddRelu();
    resolver.AddAveragePool2D();
    resolver.AddDepthwiseConv2D();
    resolver.AddMul();
    resolver.AddAdd();

    tflite::ops::micro::AllOpsResolver micro_resolver;
    tflite::SimpleMemoryAllocator tensor_arena_allocator;

    tflite::ops::micro::micro_interpreter::CreateModel(
            resolver,
            sizeof(tflite::ops::micro::AllOpsResolver),
            tensor_arena_allocator,
            nullptr
    );

    auto interpreter = std::make_unique<tflite::MicroInterpreter>(
            micro_resolver,
            tensor_arena_allocator.GetBuffer(),
            tensor_arena_allocator.GetBufferSize(),
            nullptr
    );

    interpreter->AllocateTensors();

    return interpreter;
}
