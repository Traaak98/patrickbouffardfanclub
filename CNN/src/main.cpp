//
// Created by apolline on 16/01/24.
//

// tensorflow lite
#include <tensorflow/lite/kernels/register.h>
#include <tensorflow/lite/model.h>
#include <tensorflow/lite/interpreter.h>
#include <tensorflow/lite/schema/schema_generated.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>

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
    std::cout << "Data built" << std::endl;

    // Construire le modèle CNN
    std::unique_ptr<tflite::FlatBufferModel> model =
            tflite::FlatBufferModel::BuildFromFile("../model/model.tflite");

    if (!model) {
        std::cerr << "Failed to load the model." << std::endl;
        exit(0);
    }

    tflite::ops::builtin::BuiltinOpResolver resolver;
    std::unique_ptr<tflite::Interpreter> interpreter;
    tflite::InterpreterBuilder(*model.get(), resolver)(&interpreter);
    interpreter->AllocateTensors();

    std::cout << "Model loaded" << std::endl;

    // Copiez les données audio dans le tenseur d'entrée du modèle
    float *inputTensor = interpreter->typed_input_tensor<float>(0);
    std::cout << "Input tensor loaded" << std::endl;
    std::cout << interpreter->typed_input_tensor<float>(0) << std::endl;

    for (int i = 0; i < 1024; ++i) {
        inputTensor[i] = static_cast<float>(data[0][i]);
    }

    std::cout << "Input tensor filled" << std::endl;

    // Effectuer l'inférence
    interpreter->Invoke();
    std::cout << "Inference done" << std::endl;

    // Récupérer les résultats de la prédiction
    int output_tensor_index = interpreter->outputs()[0];
    std::cout << "Output tensor index : " << output_tensor_index << std::endl;
    TfLiteIntArray* output_dims = interpreter->tensor(output_tensor_index)->dims;
    std::cout << "Output tensor dims : " << output_dims->size << std::endl;
    int output_size = 1;
    for (int i = 0; i < output_dims->size; i++) {
        output_size *= output_dims->data[i];
    }
    std::cout << "Output tensor size : " << output_size << std::endl;

    // Récupérer les résultats de l'inférence
    float *outputTensor = interpreter->typed_output_tensor<float>(0);
    std::cout << "Output tensor loaded" << std::endl;

    // Afficher les résultats (à adapter selon le format de sortie de votre modèle)
    for (int i = 0; i < output_size; i++) {
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

