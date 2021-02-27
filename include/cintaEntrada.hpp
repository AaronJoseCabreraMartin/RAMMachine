#pragma once

#include "cinta.hpp"

class cintaEntrada : public cinta{
    public:
        cintaEntrada(){}
        cintaEntrada(const std::vector<int>& cintaInicial):cinta(cintaInicial){}
        virtual ~cintaEntrada(){}
        int read(void);//no const, mueve el cabezal
};