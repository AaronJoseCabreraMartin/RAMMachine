#include "../include/load.hpp"

int load::apply(void){
    //mete lo del registro que le digas en el acu
    if ( instruction::operand_.contains(myString("="))) {
        *registryInstruction::acumulador_ = instruction::operand_.cut(1,instruction::operand_.size()-1).toInt(); 
    }else if(instruction::operand_.contains(myString("*"))) {
        if (instruction::operand_.cut(1,instruction::operand_.size()-1).toInt() <= 0) {
            std::cerr << "¡Registro inexistente!" << std::endl;
            instruction::correct_ = false;
            return 0;
        }
        //reg es el contenido del registro que tiene el *
        int reg = registryInstruction::registros_->operator[](instruction::operand_.cut(1,instruction::operand_.size()-1).toInt());
        //el acumulador debe ser el contenido del registro reg
        if (reg <= 0) {
            std::cerr << "¡Registro inexistente!" << std::endl;
            instruction::correct_ = false;
            return 0;
        }
        *registryInstruction::acumulador_ = registryInstruction::registros_->operator[](reg); 
    }else{
        *registryInstruction::acumulador_ = registryInstruction::registros_->operator[](instruction::operand_.toInt()); 
    }
    return 0;
}