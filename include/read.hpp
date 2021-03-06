#pragma once

#include<iostream>

#include "memoryInstruction.hpp"

class read : public memoryInstruction{
    private:
        int solveIndirection();
    public:
        read(const myString& line):memoryInstruction(line){}
        virtual ~read(){}
        //int apply(void);
        int apply(void){return 0;}
        virtual bool indirect(void)const{return true;}

};