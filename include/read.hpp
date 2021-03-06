#pragma once

#include<iostream>

#include "memoryInstruction.hpp"

class read : public memoryInstruction{

    public:
        read(const myString& line):memoryInstruction(line){}
        virtual ~read(){}
        int apply(void);
        virtual bool indirect(void)const{return true;}

        inline bool indirectMode(void)const{return instruction::operand_.contains(myString("*"));}
        int solveIndirection();

        myString name(void)const{return myString("read");}
};