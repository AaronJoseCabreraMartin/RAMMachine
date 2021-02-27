#include "../include/cinta.hpp"

cinta::cinta(const std::vector<int>& estadoInicial){
    for (size_t i = 0; i < estadoInicial.size(); i++) {
        cinta_.insert_tail(estadoInicial[i]);
    }
    cabezal_ = 0;
}

void cinta::show(void)const{
    for (size_t i = 0; i < cinta_.size(); i++) {
        std::cout << cinta_[i] << " ";
    }
}

void cinta::setCinta(const std::vector<int>& estado){
    cinta_.clear();
    for (size_t i = 0; i < estado.size(); i++) {
        cinta_.insert_tail(estado[i]);
    }
    cabezal_ = 0;
}
