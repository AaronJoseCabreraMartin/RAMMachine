#pragma once

#include<iostream>
#include<unordered_map>

#include "myString.hpp"
#include "registros.hpp"
#include "cinta.hpp"
#include "cintaEntrada.hpp"
#include "cintaSalida.hpp"

class instruction{
    protected:
        myString instruction_;
        
        bool hasTag_;
        bool hasOperand_;
        
        myString tag_;
        myString operand_;

        bool correct_;

    public:
        instruction(const myString&);
        virtual ~instruction(){}

        virtual int apply(void) = 0;
        virtual myString kindOf(void)const = 0;
        virtual myString name(void)const = 0;

        inline myString getInstruction(void)const{return instruction_;}
        inline myString getTag(void)const{return tag_;}
        inline myString getOperand(void)const{return operand_;}
        virtual inline bool isCorrect(void)const{return correct_;}

        inline bool hasTag(void)const{return hasTag_;}
        inline bool hasOperand(void)const{return hasOperand_;}
        inline bool inmediate(void)const{return operand_.contains(myString("="));}
        virtual bool indirect(void)const{return false;}
        virtual bool indirectMode(void)const{return false;}
        virtual int solveIndirection(void){return 0;}

        
        void show(void)const;
        void clear(void);

        virtual void stablishAcumulador(int* pointer){}
        virtual void stablishRegistros(registros* pointer){}
        virtual void stablishCintaEntrada(cintaEntrada* pointer){}
        virtual void stablishCintaSalida(cintaSalida* pointer){}
        virtual void stablishEtiquetas(std::unordered_map<std::string,unsigned>* pointer){}
        virtual void stablishEstado(bool* pointer){}
};