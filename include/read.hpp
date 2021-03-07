#pragma once

#include<iostream>

#include "memoryInstruction.hpp"

class read : public memoryInstruction{

    public:
        read(const myString& line):memoryInstruction(line){}
        virtual ~read(){}
        int apply(void);
        
        int solveIndirection();
        inline bool inmediateAllowed(void)const{return false;}
        myString name(void)const{return myString("read");}
};