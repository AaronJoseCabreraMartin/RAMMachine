#include "../include/store.hpp"

int store::solveIndirection(void){
    // eliminamos el * y cargamos el valor del registro
    int position = instruction::operand_.cut(1,instruction::operand_.size()-1).toInt();
    // devolvemos el valor del registro apuntado
    return registryInstruction::registros_->operator[](position);
}

//guarda lo que haya en el acu en el reg que le digas
int store::apply(void){
    //esta en modo indirecto
    if (instruction::operand_.contains(myString("*"))){
        registryInstruction::registros_->operator[](solveIndirection()) = *registryInstruction::acumulador_;
    //esta en modo normal
    }else{
        registryInstruction::registros_->operator[](instruction::operand_.toInt()) = *registryInstruction::acumulador_; 
    }
    
    return 0;
}
