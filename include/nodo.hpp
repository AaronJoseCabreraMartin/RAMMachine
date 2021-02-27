#pragma once

//using namespace std;


template <class T>
class nodo{
    
private:

    nodo<T>* next_;
    nodo<T>* prev_;
    T value_;

public:

    nodo( const T& value);
    //nodo( const T& value, const nodo<T>* next, const nodo<T>* prev);
    ~nodo(void);

    inline void setnext( nodo<T>* next){next_=next;}
    inline void setprev( nodo<T>* prev){prev_=prev;}
    inline void setvalue(const T& value){value_=value;}

    inline T value(void)const{return value_;}
    inline T& value(void){return value_;}
    inline nodo<T>* next(void)const{return next_;}
    inline nodo<T>* prev(void)const{return prev_;}

};

#include "../src/nodo.cpp"