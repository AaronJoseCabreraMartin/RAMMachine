#include "../include/load.hpp"

int load::apply(void){
    //mete lo del registro que le digas en el acu
    if ( instruction::operand_.contains(myString("="))) {
        *registryInstruction::acumulador_ = instruction::operand_.cut(1,instruction::operand_.size()-1).toInt(); 
    }else{
        *registryInstruction::acumulador_ = registryInstruction::registros_->operator[](instruction::operand_.toInt()); 
    }
    return 0;
}