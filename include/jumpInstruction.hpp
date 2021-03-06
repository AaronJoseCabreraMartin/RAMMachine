#pragma once

#include<iostream>
#include<unordered_map>

#include "operandInstruction.hpp"

class  jumpInstruction : public operandInstruction{
    protected:
        int* acumulador_;
        std::unordered_map<std::string,unsigned>* etiquetasInstruccion_;

    public:
        jumpInstruction(const myString& line):operandInstruction(line){}
        virtual ~jumpInstruction(){}
        virtual int apply(void) = 0;
        myString kindOf(void)const{return myString("jump");}

        void stablishAcumulador(int* pointer);
        void stablishEtiquetas(std::unordered_map<std::string,unsigned>* pointer);

};