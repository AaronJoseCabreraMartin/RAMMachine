#pragma once

#include<iostream>

#include "jumpInstruction.hpp"

class jzero : public jumpInstruction{
    public:
        jzero(const myString& line):jumpInstruction(line){}
        virtual ~jzero(){}
        //int apply(void);
        int apply(void){return 0;}
};