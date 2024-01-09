//
// Created by clara on 12/12/23.
//

#include <iostream>
#include <cassert>
#include <vector>
#include <complex>
#include <map>

#include "au_utils.h"
#include "constants.h"
#include "fft_utils.h"


std::string data_folder = "../../Data/genres_original/";
std::vector<std::string> genres = {"blues", "classical", "country", "disco", "hiphop", "jazz", "metal", "pop", "reggae",
                                   "rock"};

std::string features_folder = "../../Features/";
std::string labels = "labels/labels.csv";


void load_and_fft(std::string& filename, std::vector<float>& mean, std::vector<float>& sigma) {
    /** Load a .wav file and compute the FFT of each sample
     * @param filename: path to the .wav file
     * @param mean: vector to store the mean
     * @param sigma: vector to store the standard deviation
     */

    std::ifstream file;

// Ouverture en lecture et verification du magic number
    file.open(filename.c_str(), std::ios::binary | std::ios::in);
    if(!file.is_open())
        throw;

    assert(read32Bits(file) == RIFF_NB);
    int data_size = read32Bits(file);
    assert(read32Bits(file) == WAVE_NB);
    long curseur = file.tellg();
    file.seekg(curseur + 4 * 2, std::ios::beg); // skip "fmt " + 5 bytes (size of the chunk)
    int audio_format = read32Bits(file);
    file.seekg(curseur + 4 * 6, std::ios::beg);
    assert(read32Bits(file) == DATA_NB);
    data_size = read32Bits(file);

    std::cout << " ------------------ filename: " << filename.c_str() << " ------------------ "<< std::endl;
    std::cout << "audio_format: " << audio_format << std::endl;

// Placer le curseur au bon endroit
    curseur = file.tellg();
    file.seekg(0, std::ios::end);
    long end_file = file.tellg();
    std::cout << "length: " << end_file << std::endl;
    file.seekg(curseur, std::ios::beg);

// Creation tableau a remplir
    std::vector<Complex> x;
    int i = 0;
    float module;
    //double mean_inter = 0, sigma_inter = 0;
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
//    std::cout << "fin" << std::endl;
//    std::cout << mean.size() << " " << sigma.size() << std::endl;
//    std::cout << mean[FFT_SIZE / 2] << " " << sigma[FFT_SIZE / 2] << std::endl;
}

int main(int argc, char** argv) {
    std::vector<float> mean, sigma;
    mean.resize(FFT_SIZE);
    sigma.resize(FFT_SIZE);
    std::ofstream file_labels(features_folder + labels);
    file_labels << "label" << std::endl;

    std::ofstream file_features(features_folder + "descriptors/features.csv");
    file_features << "id,mean_vector_512,std_vector_512" << std::endl;
    int id = 0;

// Parcourir genres
    for (auto& genre : genres) {
        std::string path = data_folder + genre + "/";
        for (int i = 0; i < 100; i++) {
            std::string filename = path + genre + ".000" + std::to_string(int(i / 10)) + std::to_string(i % 10) + ".wav";
            std::cout << filename << std::endl;
// Calcul descripteurs
            load_and_fft(filename, mean, sigma);
// Ecriture dans fichiers csv
            file_features << id << ","; // << std::flush;
            for (int n = 0; n < FFT_SIZE; n++) {
                file_features << mean[n];
                if (n < FFT_SIZE - 1) file_features << ",";
            }
            file_features << ","; // << std::flush;
            for (int n = 0; n < FFT_SIZE; n++) {
                file_features << sigma[n];
                if (n < FFT_SIZE - 1) file_features << ",";
            }
            file_features << std::endl;
// Reset vecteurs
            mean.clear();
            sigma.clear();
            mean.resize(FFT_SIZE);
            sigma.resize(FFT_SIZE);
// Ecriture labels
            file_labels << id << ","; // << std::flush;
            id ++;
            file_labels << genre << ",";
        }
    }

    file_labels.close();
    file_features.close();

    return 0;
}