#pragma once

#include<iostream>

#include "mathInstruction.hpp"

class Div : public mathInstruction{
    private:
        bool* state_;
    public:
        Div(const myString& line):mathInstruction(line){}
        virtual ~Div(){}
        int apply(void);
        void stablishEstado(bool* pointer){state_ = pointer;}
        myString name(void)const{return myString("div");}
};