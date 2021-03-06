#pragma once

#include<iostream>

#include "myString.hpp"

class instruction{
    private:
        myString instruction_;
        
        bool hasTag_;
        bool hasOperand_;
        
        myString tag_;
        myString operand_;

    public:
        instruction(const myString&);
        virtual ~instruction(){}

        virtual int apply(void) = 0;
        virtual myString kindOf(void)const = 0;

        inline myString getInstruction(void)const{return instruction_;}
        inline myString getTag(void)const{return tag_;}
        inline myString getOperand(void)const{return operand_;}

        inline bool hasTag(void)const{return hasTag_;}
        inline bool hasOperand(void)const{return hasOperand_;}
        virtual bool indirect(void)const{return false;}
        
        void show(void)const;
        void clear(void);
};