#include "../include/cintaEntrada.hpp"

int cintaEntrada::read(void){
    int readValue = 0;
    if ( cinta::cabezal_ < cinta::cinta_.size()) {
        readValue = cinta::cinta_[cinta::cabezal_];
    }else{
        //std::cerr << "Error! se ha leido más de la cinta de entrada de lo que habia!" << std::endl;
        cinta::cinta_.insert_tail(0);
    }
    cinta::cabezal_++;
    return readValue;
}
