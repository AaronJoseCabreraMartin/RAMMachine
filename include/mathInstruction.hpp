#pragma once

#include<iostream>

#include "operandInstruction.hpp"

class  mathInstruction : public operandInstruction{
    public:
        mathInstruction(const myString& line):operandInstruction(line){}
        virtual ~mathInstruction(){}
        virtual int apply(void) = 0;
        myString kindOf(void)const{return myString("math");}
};