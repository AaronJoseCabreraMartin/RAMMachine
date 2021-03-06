#include "../include/write.hpp"

//escribe lo que haya en el reg que le digas en la cinta de entrada  
int write::apply(void){
    return instruction::operand_.toInt(); 
}

