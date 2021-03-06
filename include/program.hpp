#pragma once

#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include <utility> 

#include "instruction.hpp"

#include "halt.hpp"

#include "operandInstruction.hpp"

#include "jumpInstruction.hpp"
#include "jzero.hpp"
#include "jump.hpp"
#include "jgtz.hpp"

#include "mathInstruction.hpp"
#include "add.hpp"
#include "sub.hpp"
#include "mult.hpp"
#include "div.hpp"

#include "registryInstruction.hpp"
#include "store.hpp"
#include "load.hpp"

#include "memoryInstruction.hpp"
#include "read.hpp"
#include "write.hpp"

class program{
    private:
        std::vector<myString> allowedInstructions_;

        std::vector<std::pair<myString,unsigned>> taggedLines_;

        std::vector<instruction*> program_;

    public:
        program(const std::string&);
        virtual ~program();

        void showProgram(void)const;

    private:
        bool checkLineSyntax(const myString&)const;
        int checkSemantic(void)const;
        bool checkDoubleTags(void)const;
        bool checkTagDefined(const myString&)const;

        instruction* createInstruction(const myString&)const;

        myString deleteComments(const myString&)const;
        myString deleteInnerSpaces(const myString&)const;
        
        void buildInstructions(void);//
        void buildTaggedInstructions(void);//

        bool isAnInstruction(const myString&)const;//
        //bool isAJumpInstruction(const myString&)const;//
        //bool isAnIndirectInstruction(const myString&)const;//
        bool correctArgument(const instruction*)const;

        std::vector<myString> splitInstructionParts(const myString&)const;

        void clear(void);
};