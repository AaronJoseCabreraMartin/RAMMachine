#pragma once

#include<iostream>

#include "mathInstruction.hpp"

class Div : public mathInstruction{
    public:
        Div(const myString& line):mathInstruction(line){}
        virtual ~Div(){}
        //int apply(void);
        int apply(void){return 0;}
};