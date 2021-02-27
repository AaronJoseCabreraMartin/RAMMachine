#pragma once

#include<iostream>

#include "myString.hpp"

class instruction{
    private:
        myString instruction_;
        
        bool hasTag_;
        myString tag_;

        bool hasOperand_;
        myString operand_;

    public:
        instruction(const myString&);
        virtual ~instruction(){}

        inline myString getInstruction(void)const{return instruction_;}
        inline myString getTag(void)const{return tag_;}
        inline myString getOperand(void)const{return operand_;}

        inline bool hasTag(void)const{return hasTag_;}
        inline bool hasOperand(void)const{return hasOperand_;}
        
        void show(void)const;
};