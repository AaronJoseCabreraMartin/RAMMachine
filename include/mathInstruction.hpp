#pragma once

#include<iostream>

#include "operandInstruction.hpp"
#include "registros.hpp"

class  mathInstruction : public operandInstruction{
    protected:
        int* acumulador_;
        registros* registros_;
    public:
        mathInstruction(const myString& line):operandInstruction(line){}
        virtual ~mathInstruction(){}
        virtual int apply(void) = 0;
        myString kindOf(void)const{return myString("math");}

        void stablishAcumulador(int* pointer){ acumulador_ = pointer; }
        void stablishRegistros(registros* pointer){ registros_ = pointer; }

        virtual bool indirect(void)const{return true;}
        inline bool indirectMode(void)const{return instruction::operand_.contains(myString("*"));}
};