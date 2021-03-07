#pragma once

#include <vector>
#include <iostream>

#include "lista.hpp"

class cinta{
    protected:
        lista<int> cinta_;
        unsigned cabezal_;
    public:
        cinta(){}
        cinta(const std::vector<int>&);
        virtual ~cinta(){}

        virtual void show(void)const;
        
        inline int size(void)const{return cinta_.size();}

        void setCinta(const std::vector<int>&);
};