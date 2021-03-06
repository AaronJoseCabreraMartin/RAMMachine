#pragma once

#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include <unordered_map> 

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

        std::unordered_map<std::string,unsigned> taggedLines_;

        std::vector<instruction*> program_;

        bool duplicateTags_;

        char comments_;

    public:
        program(const std::string&);
        virtual ~program();

        void showProgram(void)const;

        inline unsigned size(void)const{return program_.size();}

        instruction* operator[](const int& i)const{return program_[i];}
    
        std::unordered_map<std::string,unsigned>* getEtiquetas(void);

    private:
        bool checkLineSyntax(const myString&)const;
        int checkSemantic(void);
        bool checkTagDefined(const myString&);

        instruction* createInstruction(const myString&)const;

        myString deleteComments(const myString&)const;
        myString deleteInnerSpaces(const myString&)const;
        
        void buildInstructions(void);//
        void buildTaggedInstructions(void);//

        bool correctArgument(const instruction*)const;

        std::vector<myString> splitInstructionParts(const myString&)const;

        void clear(void);

};