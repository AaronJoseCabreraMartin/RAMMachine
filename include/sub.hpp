#pragma once

#include<iostream>

#include "mathInstruction.hpp"

class sub : public mathInstruction{
    public:
        sub(const myString& line):mathInstruction(line){}
        virtual ~sub(){}
        int apply(void);
        myString name(void)const{return myString("sub");}
};