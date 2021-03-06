#pragma once

#include<iostream>

#include "operandInstruction.hpp"
#include "registros.hpp"

class  registryInstruction : public operandInstruction{
    protected:
        int* acumulador_;
        registros* registros_;
    public:
        registryInstruction(const myString& line):operandInstruction(line){}
        virtual ~registryInstruction(){}
        virtual int apply(void) = 0;
        myString kindOf(void)const{return myString("registry");}

        void stablishAcumulador(int* pointer){ acumulador_ = pointer; }
        void stablishRegistros(registros* pointer){ registros_ = pointer; }
};