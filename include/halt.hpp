#pragma once

#include "instruction.hpp"

class halt : public instruction{
    public:
        halt(const myString& line): instruction(line){}
        virtual ~halt(){}

        inline myString kindOf(void)const{return myString("halt");} 
        inline int apply(void){return 0;}

        inline bool hasOperand(void)const{return false;}
        myString name(void)const{return myString("halt");}
};