#pragma once

#include<iostream>

#include "registryInstruction.hpp"

class store : public registryInstruction{
    public:
        store(const myString& line):registryInstruction(line){}
        virtual ~store(){}
        //int apply(void);
        int apply(void){return 0;}
        virtual bool indirect(void)const{return true;}
};