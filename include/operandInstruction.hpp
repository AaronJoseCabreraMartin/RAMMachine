#pragma once

#include<iostream>

#include "instruction.hpp"

class operandInstruction : public instruction{
    public:
        operandInstruction(const myString& line):instruction(line){}
        virtual ~operandInstruction(){}
        virtual int apply(void) = 0;
        virtual myString kindOf(void)const = 0;
};