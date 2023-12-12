//
// Created by clara on 12/12/23.
//

#include "au_utils.h"

std::string filename = "../../Audio/blues.00000.au";

int main(int argc, char** argv) {
    std::ifstream file;

    // Ouverture en lecture + données binaires :
    file.open(filename.c_str(), std::ios::binary | std::ios::in);
    if(!file.is_open())
        throw;



    return 0;
}