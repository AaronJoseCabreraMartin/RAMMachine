#pragma once

#include<iostream>

#include "operandInstruction.hpp"

class  memoryInstruction : public operandInstruction{
    protected:
        int* acumulador_;
        registros* registros_;
        cintaEntrada* cintaEntrada_;
        cintaSalida* cintaSalida_;
    
    public:
        memoryInstruction(const myString& line):operandInstruction(line){}
        virtual ~memoryInstruction(){}
        virtual int apply(void) = 0;
        myString kindOf(void)const{return myString("memory");}

        void stablishAcumulador(int* pointer){ acumulador_ = pointer; }
        void stablishRegistros(registros* pointer){ registros_ = pointer; }
        void stablishCintaEntrada(cintaEntrada* pointer){cintaEntrada_ = pointer;}
        void stablishCintaSalida(cintaSalida* pointer){cintaSalida_ = pointer;}
};