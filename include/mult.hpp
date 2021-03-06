#pragma once

#include<iostream>

#include "mathInstruction.hpp"

class mult : public mathInstruction{
    public:
        mult(const myString& line):mathInstruction(line){}
        virtual ~mult(){}
        //int apply(void);
        int apply(void){return 0;}
};