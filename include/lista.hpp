#include <iostream>
#include "nodo.hpp"
#pragma once

#include<cassert>

//using namespace std;

template <class T>
class lista{
    
private:

    nodo<T>* head_;
    nodo<T>* tail_;
    int size_;//tamaño de la lista
    
public:

  lista(void);
  lista(const lista<T>& lista);
  ~lista(void){destroy();}

  T operator[](int i)const;
  lista<T>& operator=(const lista<T> lista);
  bool operator==(const lista<T> lista)const;
  inline bool operator!=(const lista <T> lista)const{return !(*this==lista);}

  inline T head_value(void)const{return head_->value();}
  inline T tail_value(void)const{return tail_->value();}

  inline nodo<T>* head(void)const{return head_;}
  inline nodo<T>* tail(void)const{return tail_;}

  void pop_tail(void);
  void pop_head(void);

  void insert_tail( nodo<T>* nodo );
  void insert_tail( T value ){insert_tail( new nodo<T>(value) );}
  
  void insert_head(nodo<T>* nodo);
  void insert_head( T value ){insert_head( new nodo<T>(value) );}
  
  nodo<T>* extract_head(void);
  nodo<T>* extract_tail(void);

  inline bool empty(void)const{return size_==0;} 
  
  inline int size(void)const{return size_;}
  inline void clear(void){destroy();}

  void fill( T value );
  void set_value(T value,int i);
  T get_value(int i)const;
  
  nodo<T>* extract(int pos);
  void erase(int pos);
private:
  void destroy(void);
};

#include "../src/lista.cpp"