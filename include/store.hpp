#pragma once

#include<iostream>

#include "registryInstruction.hpp"

class store : public registryInstruction{
    private:
        int solveIndirection(void);
    public:
        store(const myString& line):registryInstruction(line){}
        virtual ~store(){}
        int apply(void);

        inline bool inmediateAllowed(void)const{return false;}
        myString name(void)const{return myString("store");}
};