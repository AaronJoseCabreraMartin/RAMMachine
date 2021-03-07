#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "../include/cintaEntrada.hpp"
#include "../include/cintaSalida.hpp"
#include "../include/program.hpp"
#include "../include/registros.hpp"

class RAMMachine{
    //friend class Div;
    private:
        cintaEntrada cintaEntrada_;
        cintaSalida cintaSalida_;
        std::string ficheroSalida_;

        program programa_;

        unsigned programCounter_;
        int acumulador_;
        unsigned instruccionesEjecutadas_;

        bool state_;//HALT or RUNNING
        bool debug_;

        registros registros_;
    public:
        //cinta entrada, salida, programa, modo
        RAMMachine(const std::string&,const std::string&,const std::string&,const bool& debug = false);
        virtual ~RAMMachine(){}

        inline bool state(void)const{return state_;}
        inline unsigned instruccionesEjecutadas(void)const{return instruccionesEjecutadas_;}

        void show(void)const;
        void showState(void)const;
        void showRegisters(void)const;
        void showCintaEntrada(void)const;
        void showCintaSalida(void)const;
        void showPrograma(void)const;

        inline void exportToFile(void)const{cintaSalida_.toFile(ficheroSalida_);}
        inline bool programSize(void)const{return programa_.size();}
        //ejecuta hasta un halt o un error
        void execute(void);
        //Para modo paso a paso
        void executeStepByStep(void);
    private:
        void applyInstrucction(void);

        void setPointers(void);
};