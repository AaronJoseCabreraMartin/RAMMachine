#pragma once

#include<iostream>

#include "memoryInstruction.hpp"

class write : public memoryInstruction{
    public:
        write(const myString& line):memoryInstruction(line){}
        virtual ~write(){}
        //int apply(void);
        int apply(void){return 0;}
};