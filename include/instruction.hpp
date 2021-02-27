#pragma once

#include<iostream>

#include "myString.hpp"

class instruction{
    private:
        myString instruction_;
        bool hasTag_;
        myString tag_;
    public:
        instruction(const myString&);
        virtual ~instruction(){}

        inline myString getInstruction(void)const{return instruction_;}
        inline myString getTag(void)const{return tag_;}
        inline bool hasTag(void)const{return hasTag_;}
        void show(void)const;
};