#pragma once

#include<iostream>

#include "mathInstruction.hpp"

class add : public mathInstruction{
    public:
        add(const myString& line):mathInstruction(line){}
        virtual ~add(){}
        int apply(void);
        myString name(void)const{return myString("add");}
};