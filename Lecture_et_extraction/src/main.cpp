//
// Created by clara on 12/12/23.
//

#include <iostream>
#include <cassert>
#include <vector>
#include "au_utils.h"
#include "constants.h"

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

void load_and_fft(std::string& filename) {
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



}

int main(int argc, char** argv) {


    return 0;
}