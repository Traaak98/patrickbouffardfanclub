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


std::string data_folder = "../../Data/genres_original/";
std::vector<std::string> genres = {"blues", "classical", "country", "disco", "hiphop", "jazz", "metal", "pop", "reggae",
                                   "rock"};

std::string features_folder = "../../Features/";
std::string labels = "labels.csv";

void load_and_fft(std::string& filename, std::vector<float>& mean, std::vector<float>& sigma) {
    std::ifstream file;

// Ouverture en lecture et verification du magic number
    file.open(filename.c_str(), std::ios::binary | std::ios::in);
    if(!file.is_open())
        throw;

    assert(read32Bits(file) == RIFF_NB);
    int data_size = read32Bits(file);
    assert(read32Bits(file) == WAVE_NB);
    int data_offset = read32Bits(file);

    std::cout << " ------------------ filename: " << filename.c_str() << " ------------------ "<< std::endl;
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
            j ++;
            ite_dit_fft(x);
            for (int n = 1; n < FFT_SIZE + 1; n++) {
                module = std::norm(x[n - 1]) * 2 / x.size();     // xj_n
                mean[n - 1] += module;
            }
            x.clear();
            i = 0;
        }

        else if (i == FFT_SIZE) {
            j ++;
            ite_dit_fft(x);
            for (int n = 0; n < FFT_SIZE; n++) {
                module = std::norm(x[n]) * 2 / x.size();     // xj_n
                mean[n] += module;
                sigma[n] += (j * module - mean[n]) * (j * module - mean[n]) / (j * (j - 1));
            }
            x.clear();
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

// Parcourir genres
    for (auto& genre : genres) {
        std::string path = data_folder + genre + "/";
        for (int i = 0; i < 100; i++) {
            std::string filename = path + genre + ".000" + std::to_string(int(i / 10)) + std::to_string(i % 10) + ".wav";
            std::cout << filename << std::endl;
            load_and_fft(filename, mean, sigma);
            std::string results = features_folder + genre + "/" + genre + ".000" + std::to_string(int(i / 10)) + std::to_string(i % 10) + ".csv";
            std::cout << results << std::endl;
            std::ofstream file(results);
            for (int n = 0; n < FFT_SIZE; n++) {
                file << mean[n];
                file << ",";
            }
            file.seekp(-1, std::ios::end);
            file.write("", 1); // erase last comma
            file.write("\n", 1);
            for (int n = 0; n < FFT_SIZE; n++) {
                file << sigma[n];
                file << ",";
            }
            file.seekp(-1, std::ios::end);
            file.write("", 1); // erase last comma
            file.close();
            mean.clear();
            sigma.clear();
        }
    }

    return 0;
}