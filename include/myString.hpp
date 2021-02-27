#pragma once
#include<string>

class myString{
    private:
        std::string string_;
    public:
        myString(void){}
        myString(const std::string& string){ string_ = string; }
        virtual ~myString(){}
        
        bool operator==(const myString&)const;
        inline char operator[](const int& index)const{return string_[index];}

        inline unsigned size(void)const{return string_.size();}
        inline std::string string(void)const{return string_;}

        void set(const std::string&);

        myString capitalize(void)const;

        inline operator std::string() const{return string_;}

        //myString cut(const unsigned& inicio, const unsigned& fin = 0)const;
        //bool contains(const myString&)const;
};