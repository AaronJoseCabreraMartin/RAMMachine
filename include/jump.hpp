#pragma once

#include<iostream>

#include "jumpInstruction.hpp"

class jump : public jumpInstruction{
    public:
        jump(const myString& line):jumpInstruction(line){}
        virtual ~jump(){}
        //int apply(void);
        int apply(void){return 0;}
};