#pragma once

#include<iostream>

#include "registryInstruction.hpp"

class load : public registryInstruction{
    public:
        load(const myString& line):registryInstruction(line){}
        virtual ~load(){}
        int apply(void);

        myString name(void)const{return myString("load");}

};