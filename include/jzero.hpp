#pragma once

#include<iostream>

#include "jumpInstruction.hpp"

class jzero : public jumpInstruction{
    public:
        jzero(const myString& line):jumpInstruction(line){}
        virtual ~jzero(){}
        int apply(void);
        myString name(void)const{return myString("jzero");}
};