#pragma once

#include<iostream>

#include "registryInstruction.hpp"

class load : public registryInstruction{
    private:
        int solveIndirection();
    public:
        load(const myString& line):registryInstruction(line){}
        virtual ~load(){}
        //int apply(void);
        int apply(void){return 0;}
};