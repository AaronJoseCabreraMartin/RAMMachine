#pragma once

#include<iostream>

#include "operandInstruction.hpp"

class  registryInstruction : public operandInstruction{
    public:
        registryInstruction(const myString& line):operandInstruction(line){}
        virtual ~registryInstruction(){}
        virtual int apply(void) = 0;
        myString kindOf(void)const{return myString("registry");}
};