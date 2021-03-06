#pragma once

#include<iostream>

#include "operandInstruction.hpp"

class  memoryInstruction : public operandInstruction{
    public:
        memoryInstruction(const myString& line):operandInstruction(line){}
        virtual ~memoryInstruction(){}
        virtual int apply(void) = 0;
        myString kindOf(void)const{return myString("memory");}
};