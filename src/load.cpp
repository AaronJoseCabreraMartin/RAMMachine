#include "../include/load.hpp"

int load::apply(void){
    //mete lo del registro que le digas en el acu
    *registryInstruction::acumulador_ = registryInstruction::registros_->operator[](instruction::operand_.toInt()); 
    return 0;
}