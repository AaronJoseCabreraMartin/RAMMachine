#pragma once

#include <string>
#include <fstream>

#include "cinta.hpp"

class cintaSalida : public cinta{
    public:
        cintaSalida(){}
        cintaSalida(const std::vector<int>& cintaInicial):cinta(cintaInicial){}
        virtual ~cintaSalida(){}
        void write(const int&);
        void toFile(const std::string&)const;
        void show(void)const;
};