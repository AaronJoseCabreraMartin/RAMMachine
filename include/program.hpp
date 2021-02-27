#pragma once

#include<iostream>
#include<vector>
#include<string>
#include<fstream>

#include "instruction.hpp"

class program{
    private:
        std::vector<myString> allowedInstructions_;
        std::vector<instruction> program_;
    public:
        program(const std::string&);
        ~program(){}

        void showProgram(void)const;

    private:
        bool checkLineSyntax(const myString&)const;
        int checkSemantic(void)const;
        myString deleteComments(const myString&)const;
        void buildInstructions(void);
};