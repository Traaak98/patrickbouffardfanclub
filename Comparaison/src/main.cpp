//
// Created by apolline on 29/01/24.
//

#include <tensorflow/lite/kernels/register.h>
#include <tensorflow/lite/model.h>
#include <tensorflow/lite/interpreter.h>
#include <tensorflow/lite/schema/schema_generated.h>
#include <tensorflow/lite/profiling/profiler.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <chrono>
#include "svm.h"
#include <memory>
#include <sys/resource.h>
#include "random_forest.h"
#include "decision_tree.h"

struct svm_node *x_space;
struct svm_model *model;

void CNN(const float* data, std::map<int, std::string> labels_map);
void SVM(const float* data, std::map<int, std::string> labels_map);
void RF(float* data, std::map<int, std::string> labels_map);
void DT(float* data, std::map<int, std::string> labels_map);

std::size_t getCurrentMemoryUsage();

int main(int argc, char** argv) {
    if (argc != 2){
        exit(0);
    }

    std::string filename = argv[1];

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

    std::map<int, std::string> labels_map2;
    labels_map2[1] = "blues";
    labels_map2[2] = "classical";
    labels_map2[3] = "country";
    labels_map2[4] = "disco";
    labels_map2[5] = "hiphop";
    labels_map2[6] = "jazz";
    labels_map2[7] = "metal";
    labels_map2[8] = "pop";
    labels_map2[9] = "reggae";
    labels_map2[10] = "rock";

    float data[1024];
    std::string cell;
    std::ifstream results_data_file(filename);

    for (int j = 0; j < 1024; ++j){
        std::getline(results_data_file, cell, ',');
        data[j] = std::stof(cell);
    }

    // CNN :
    CNN(data, labels_map2);

    // SVM :
    SVM(data, labels_map2);

    // RF :
    RF(data, labels_map2);

    // DT :
    DT(data, labels_map2);

    return 0;
}

void CNN(float* data, std::map<int, std::string> labels_map){


    // Build vectors data

    std::cout << "Data built" << std::endl;

    // Construire le modèle CNN
    std::unique_ptr<tflite::FlatBufferModel> model =
            tflite::FlatBufferModel::BuildFromFile("../../CNN/model/model.tflite");

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
        inputTensor[i] = static_cast<float>(data[i]);
    }

    std::cout << "Input tensor filled" << std::endl;

    // Effectuer l'inférence
    std::size_t first = getCurrentMemoryUsage();
    auto start_time = std::chrono::high_resolution_clock::now();
    interpreter->Invoke();
    auto end_time = std::chrono::high_resolution_clock::now();
    auto inference_duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::size_t second = getCurrentMemoryUsage();
    std::cout << "Temps d'inférence : " << inference_duration.count() << " microsecondes" << std::endl;
    std::cout << "Mémoire allocation = " << second - first << " bytes." << std::endl;
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
        std::cout << "Classe " << labels_map[i+1] << " : " << outputTensor[i] << std::endl;
    }
}

void SVM(float* data, std::map<int, std::string> labels_map){
    model = svm_load_model("../../SVM/svm.model");
    // Allouer un tableau de svm_node
    struct svm_node *svmNodes = new svm_node[1024 + 1];  // +1 pour le dernier élément avec index = -1

    // Remplir le tableau svm_node avec les données
    for (int i = 0; i < 1024; ++i) {
        svmNodes[i].index = i + 1;  // L'index commence généralement à 1 dans LIBSVM
        svmNodes[i].value = data[i];
    }
    std::size_t first = getCurrentMemoryUsage();
    auto start_time = std::chrono::high_resolution_clock::now();
    double pred = svm_predict(model, x_space);
    auto end_time = std::chrono::high_resolution_clock::now();
    std::size_t second = getCurrentMemoryUsage();
    auto inference_duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Temps d'inférence : " << inference_duration.count() << " microsecondes" << std::endl;
    std::cout << "Mémoire allocation = " << second - first << " bytes." << std::endl;
    std::cout << "Inference done" << std::endl;
    std::cout << "Prédiction : " << labels_map[int(pred)]<< std::endl;

}

void RF(float* data, std::map<int, std::string> labels_map){
    std::size_t first = getCurrentMemoryUsage();
    auto start_time = std::chrono::high_resolution_clock::now();
    std::int32_t j = random_forest_predict(data, 1024);
    auto end_time = std::chrono::high_resolution_clock::now();
    std::size_t second = getCurrentMemoryUsage();
    auto inference_duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Temps d'inférence : " << inference_duration.count() << " microsecondes" << std::endl;
    std::cout << "Mémoire allocation = " << second - first << " bytes." << std::endl;
    std::cout << "Prédiction : " << labels_map[j] << std::endl;

}

void DT(float* data, std::map<int, std::string> labels_map){
    std::size_t first = getCurrentMemoryUsage();
    auto start_time = std::chrono::high_resolution_clock::now();
    std::int32_t j = decision_tree_predict(data, 1024);
    auto end_time = std::chrono::high_resolution_clock::now();
    std::size_t second = getCurrentMemoryUsage();
    auto inference_duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Temps d'inférence : " << inference_duration.count() << " microsecondes" << std::endl;
    std::cout << "Mémoire allocation = " << second - first << " bytes." << std::endl;
    std::cout << "Prédiction : " << labels_map[j] << std::endl;

}


std::size_t getCurrentMemoryUsage() {
    // Utiliser la bibliothèque standard C++ pour allouer et libérer de la mémoire
    void* dummy_memory = malloc(1); // Allouer une petite quantité de mémoire
    free(dummy_memory); // Libérer la mémoire

    // Utiliser getrusage pour mesurer la mémoire résidente
    struct rusage usage;
    if (getrusage(RUSAGE_SELF, &usage) == 0) {
        return static_cast<std::size_t>(usage.ru_maxrss);
    }

    return 0;
}
