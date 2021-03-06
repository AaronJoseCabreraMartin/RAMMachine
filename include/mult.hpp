#pragma once

#include<iostream>

#include "mathInstruction.hpp"

class mult : public mathInstruction{
    public:
        mult(const myString& line):mathInstruction(line){}
        virtual ~mult(){}
        int apply(void);
        myString name(void)const{return myString("mult");}
};