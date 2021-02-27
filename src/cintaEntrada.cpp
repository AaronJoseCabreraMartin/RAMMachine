#include "../include/cintaEntrada.hpp"

int cintaEntrada::read(void){
    int readValue = cinta::cinta_[cinta::cabezal_];
    cinta::cabezal_++;
    return readValue;
}
