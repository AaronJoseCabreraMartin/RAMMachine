#pragma once

#include<vector>

#include "lista.hpp"

class registros{
    private:
        lista<int> registros_;
    
    public:
        registros(void){}
        registros(const std::vector<int>&);
        virtual ~registros(){}

        int operator[](const int&)const;
        int& operator[](const int&);

        int at(int);

        void show(void)const;
        inline unsigned size(void)const{return registros_.size();} 

        void set(const std::vector<int>&);
};