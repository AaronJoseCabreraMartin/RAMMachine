#pragma once

#include<iostream>

#include "memoryInstruction.hpp"

class write : public memoryInstruction{
    public:
        write(const myString& line):memoryInstruction(line){}
        virtual ~write(){}
        int apply(void);
        myString name(void)const{return myString("write");}
};