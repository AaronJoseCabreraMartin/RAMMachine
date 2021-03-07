#include "../include/cintaEntrada.hpp"

int cintaEntrada::read(void){
    int readValue = 0;
    if ( cinta::cabezal_ < cinta::cinta_.size()) {
        readValue = cinta::cinta_[cinta::cabezal_];
    }else{
        std::cerr << "Se ha leido más de la cinta de entrada de lo que habia!" << std::endl;
        std::cerr << "Se ha devuelto un 0" << std::endl;
        cinta::cinta_.insert_tail(0);
    }
    cinta::cabezal_++;
    return readValue;
}


void cintaEntrada::show(void)const{
    for (size_t i = 0; i < cinta_.size(); i++) {
        std::cout << cinta_[i] << " ";
    }
}