//
// Created by clara on 12/12/23.
//

#include <iostream>
#include <cassert>
#include <vector>
#include <complex>
#include "au_utils.h"
#include "constants.h"
#include "fft_utils.h"


std::string audio_test = "../../Audio/blues.00000.au";

void load_and_save(std::string& filename) {
    std::ifstream file;

// Ouverture en lecture et verification du magic number
    file.open(filename.c_str(), std::ios::binary | std::ios::in);
    if(!file.is_open())
        throw;

    assert(read32Bits(file) == MAGIC_NB);
    int data_offset = read32Bits(file);
    int data_size = read32Bits(file);

    std::cout << "data_offset: " << data_offset << std::endl;
    std::cout << "data_size: " << data_size << std::endl;

// Placer le curseur au bon endroit
    file.seekg(0, std::ios::beg);
    file.seekg(data_offset, std::ios::beg);
    int end_file = data_offset + data_size;
    long curseur = file.tellg();

// Creation tableau a remplir
//    int data[data_size];
//    int i = 0;
    std::ofstream results("signal.csv");
    // alloc dynamique auto* data2 = new int16_t[data_size];
    while (curseur < end_file) {
        results << readSample(file);
        results << ",";
        curseur = file.tellg();
    }

// Close file and write data in .csv for testing purposes
    file.close();
    results.seekp(-1, std::ios::end);
    results.write("", 1); // erase last comma
    results.close();
}

void load_and_fft(std::string& filename, std::vector<float>& mean, std::vector<float>& sigma) {
    std::ifstream file;

// Ouverture en lecture et verification du magic number
    file.open(filename.c_str(), std::ios::binary | std::ios::in);
    if(!file.is_open())
        throw;

    assert(read32Bits(file) == MAGIC_NB);
    int data_offset = read32Bits(file);
    int data_size = read32Bits(file);

    std::cout << "data_offset: " << data_offset << std::endl;
    std::cout << "data_size: " << data_size << std::endl;

// Placer le curseur au bon endroit
    file.seekg(0, std::ios::beg);
    file.seekg(data_offset, std::ios::beg);
    int end_file = data_offset + data_size;
    long curseur = file.tellg();

// Creation tableau a remplir
    std::vector<Complex> x;
    int i = 0;
    float module;
    double mean_inter = 0, sigma_inter = 0;
    int j = 0;

    while (curseur < end_file) {
        i ++;
        x.emplace_back(readSample(file));
        curseur = file.tellg();
        if (i == FFT_SIZE && j == 0) {
            std::cout << "dans le morceau n° " << j << std::endl;
            j ++;
            std::cout << x.size() << std::endl;
            ite_dit_fft(x);
            std::cout << "calcul itératif" << std::endl;
            for (int n = 1; n < FFT_SIZE + 1; n++) {
                module = std::norm(x[n - 1]) * 2 / x.size();     // xj_n
                mean[n - 1] += module;
            }
            std::cout << mean.size() << " " << sigma.size() << std::endl;
            std::cout << mean[FFT_SIZE / 2] << " " << sigma[FFT_SIZE / 2] << std::endl;
            x.clear();
            std::cout << x.size() << std::endl;
            i = 0;
        }

        else if (i == FFT_SIZE) {
            std::cout << "dans le morceau n° " << j << std::endl;
            j ++;
            std::cout << x.size() << std::endl;
            ite_dit_fft(x);
            std::cout << "calcul itératif" << std::endl;
            for (int n = 0; n < FFT_SIZE; n++) {
                module = std::norm(x[n]) * 2 / x.size();     // xj_n
                mean[n] += module;
                sigma[n] += (j * module - mean[n]) * (j * module - mean[n]) / (j * (j - 1));
            }
            std::cout << mean.size() << " " << sigma.size() << std::endl;
            std::cout << mean[FFT_SIZE / 2] << " " << sigma[FFT_SIZE / 2] << std::endl;
            x.clear();
            std::cout << x.size() << std::endl;
            i = 0;
        }
    }

    for (int n = 0; n < FFT_SIZE; n++) {
        mean[n] /= j;
        sigma[n] = std::sqrt(sigma[n]) / j;
    }
    std::cout << "fin" << std::endl;
    std::cout << mean.size() << " " << sigma.size() << std::endl;
    std::cout << mean[FFT_SIZE / 2] << " " << sigma[FFT_SIZE / 2] << std::endl;

}

int main(int argc, char** argv) {
    std::vector<float> mean, sigma;
    mean.resize(FFT_SIZE);
    sigma.resize(FFT_SIZE);
    std::cout << "debut" << std::endl;
    std::cout << mean.size() << " " << sigma.size() << std::endl;
    std::cout << mean[FFT_SIZE / 2] << " " << sigma[FFT_SIZE / 2] << std::endl;
    load_and_fft(audio_test, mean, sigma);

    std::ofstream results_mean("fft_mean.csv");
    std::ofstream results_sigma("fft_sigma.csv");
    // alloc dynamique auto* data2 = new int16_t[data_size];
    for (int n = 0; n < FFT_SIZE; n++) {
        results_mean << mean[n];
        results_sigma << sigma[n];
        results_mean << ",";
        results_sigma << ",";
    }

// Close file and write data in .csv for testing purposes
    results_mean.seekp(-1, std::ios::end);
    results_mean.write("", 1); // erase last comma
    results_sigma.seekp(-1, std::ios::end);
    results_sigma.write("", 1); // erase last comma
    results_mean.close();
    results_sigma.close();
    return 0;
}