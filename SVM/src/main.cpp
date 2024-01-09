//
// Created by apolline on 09/01/24.
//

#include <iostream>
#include <fstream>
#include <vector>
#include "svm.h"
#include <map>
#include <string>

struct svm_parameter param;		// set by parse_command_line
struct svm_problem prob;
struct svm_node *x_space;
struct svm_model *model;

#define Malloc(type,n) (type *)malloc((n)*sizeof(type))

void svm(std::string& results_data, std::string& results_labels, std::map<std::string, int> labels_map){

    //set all default parameters for param struct
    param.svm_type = C_SVC;
    param.kernel_type = RBF;
    param.degree = 3;
    param.gamma = 0;	// 1/num_features
    param.coef0 = 0;
    param.nu = 0.5;
    param.cache_size = 100;
    param.C = 1;
    param.eps = 1e-3;
    param.p = 0.1;
    param.shrinking = 1;
    param.probability = 0;
    param.nr_weight = 0;
    param.weight_label = NULL;
    param.weight = NULL;

    // build labels and data vectors
    std::vector<int> labels;
    std::vector<std::vector<double>> data;
    std::ifstream results_data_file(results_data);
    std::ifstream labels_file(results_labels);
    std::string cell;

    while(std::getline(labels_file, cell, ',')){
        int ind = labels_map[cell];
        labels.push_back(ind);
    }

    std::cout << "labels size: " << labels.size() << std::endl; // should be 1000

    for (int i = 0; i < 1000; ++i){
        std::vector<double> data_line;
        for (int j = 0; j < 1024; ++j){
            std::getline(results_data_file, cell, ',');
            data_line.push_back(std::stod(cell));
        }
        std::getline(results_data_file, cell, '\n');
        data.push_back(data_line);
    }

    std::cout << "data size: " << data.size() << std::endl; // should be 1000
    std::cout << "data size line: " << data[0].size() << std::endl; // should be 1024

    // set value of prob struct
    prob.l = 1000; // number of lines with labels
    prob.y = Malloc(double,prob.l); //space for prob.l doubles
    prob.x = Malloc(struct svm_node *, prob.l); //space for prob.l pointers to struct svm_node
    x_space = Malloc(struct svm_node, 1025 * prob.l); //memory for pairs of index/value

    // fill prob struct
    for (int i=0; i < prob.l; ++i){prob.y[i] = labels[i];}

    int j=0; //counter to traverse x_space[i];
    for (int i=0;i < prob.l; ++i)
    {
        //set i-th element of prob.x to the address of x_space[j].
        //elements from x_space[j] to x_space[j+data[i].size] get filled right after next line
        prob.x[i] = &x_space[j];
        for (int k=0; k < data[i].size(); ++k, ++j)
        {
            x_space[j].index=k+1; //index of value
            x_space[j].value=data[i][k]; //value
        }
        x_space[j].index=-1;//state the end of data vector
        x_space[j].value=0;
        j++;
    }

    // train model
    model = svm_train(&prob, &param);

    std::cout << "nb_classe" << model->nr_class << std::endl;

}

int main(int argc, char** argv) {

    std::string results_labels = "../data/labels.csv";
    std::string results_data = "../data/dataset.csv";

    // create map
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


    svm(results_data, results_labels, labels_map);

    return 0;
}