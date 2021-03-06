#pragma once

#include<iostream>

#include "mathInstruction.hpp"

class sub : public mathInstruction{
    public:
        sub(const myString& line):mathInstruction(line){}
        virtual ~sub(){}
        //int apply(void);
        int apply(void){return 0;}
};