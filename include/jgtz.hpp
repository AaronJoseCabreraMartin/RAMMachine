#pragma once

#include<iostream>

#include "jumpInstruction.hpp"

class jgtz : public jumpInstruction{
    public:
        jgtz(const myString& line):jumpInstruction(line){}
        virtual ~jgtz(){}
        int apply(void);
        myString name(void)const{return myString("jgtz");}
};