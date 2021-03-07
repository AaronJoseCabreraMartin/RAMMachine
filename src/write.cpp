#include "../include/write.hpp"

//escribe lo que haya en el reg que le digas en la cinta de entrada  
int write::apply(void){
    if ( instruction::inmediate() ){
        return instruction::operand_.cut(1,instruction::operand_.size()-1).toInt(); 
    }
    return instruction::operand_.toInt(); 
}

