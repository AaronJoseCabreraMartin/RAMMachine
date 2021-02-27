#pragma once

#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include <utility> 

#include "instruction.hpp"

class program{
    private:
        std::vector<myString> allowedInstructions_;
        std::vector<myString> jumpInstructions_;
        std::vector<myString> indirectInstructons_;//instrucciones que admiten indireccion

        std::vector<std::pair<myString,unsigned>> taggedLines_;

        std::vector<instruction> program_;

    public:
        program(const std::string&);
        ~program(){}

        void showProgram(void)const;

    private:
        bool checkLineSyntax(const myString&)const;
        int checkSemantic(void)const;
        bool checkDoubleTags(void)const;
        bool checkTagDefined(const myString&)const;

        myString deleteComments(const myString&)const;
        
        void buildInstructions(void);
        void buildTaggedInstructions(void);

        bool isAnInstruction(const myString&)const;
        bool isAJumpInstruction(const myString&)const;
        bool isAnIndirectInstruction(const myString&)const;
        bool correctArgument(const instruction&)const;

};