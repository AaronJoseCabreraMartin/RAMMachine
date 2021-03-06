#include "../include/cintaSalida.hpp"

void cintaSalida::write(const int& toWrite){
    cinta::cinta_.insert_tail(toWrite);
    cinta::cabezal_++;
}

void cintaSalida::show(void)const{
    for (size_t i = 0; i < cinta_.size(); i++) {
        std::cout << cinta_[i] << " ";
    }
}

void cintaSalida::toFile(const std::string& toExport)const{
    std::ofstream fs(toExport);
    for (size_t i = 0; i < cinta::cinta_.size(); i++) {
        fs << cinta::cinta_[i] << " ";
    }
    fs.close();
}