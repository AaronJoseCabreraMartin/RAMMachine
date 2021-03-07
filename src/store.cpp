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
        if (instruction::operand_.cut(1,instruction::operand_.size()-1).toInt() <= 0) {
            std::cerr << "¡Registro inexistente!" << std::endl;
            instruction::correct_ = false;
            return 0;
        }
        if (solveIndirection() <= 0) {
            std::cerr << "¡Registro inexistente!" << std::endl;
            instruction::correct_ = false;
            return 0;
        }
        registryInstruction::registros_->operator[](solveIndirection()) = *registryInstruction::acumulador_;
    //esta en modo normal
    }else{
        if (instruction::operand_.toInt() <= 0) {
            std::cerr << "¡Registro inexistente!" << std::endl;
            instruction::correct_ = false;
            return 0;
        }
        registryInstruction::registros_->operator[](instruction::operand_.toInt()) = *registryInstruction::acumulador_; 
    }
    
    return 0;
}
