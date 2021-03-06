#pragma once

#include<iostream>

#include "operandInstruction.hpp"

class  jumpInstruction : public operandInstruction{
    public:
        jumpInstruction(const myString& line):operandInstruction(line){}
        virtual ~jumpInstruction(){}
        virtual int apply(void) = 0;
        myString kindOf(void)const{return myString("jump");}
};