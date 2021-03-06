#pragma once

#include<iostream>

#include "jumpInstruction.hpp"

class jgtz : public jumpInstruction{
    public:
        jgtz(const myString& line):jumpInstruction(line){}
        virtual ~jgtz(){}
        //int apply(void);
        int apply(void){return 0;}
};