#include "../include/add.hpp"

int add::apply(void){
    int valueOperand;
    //si es carga inmediata, se coge ese valor directamente
    if ( instruction::operand_.contains(myString("=")) ) {
        valueOperand = instruction::operand_.cut(1,instruction::operand_.size()-1).toInt();
    //si es indirecta debemos devolver el registro en el que hay que mirar
    }else if(instruction::operand_.contains(myString("*"))) {
        if (instruction::operand_.cut(1,instruction::operand_.size()-1).toInt() <= 0) {
            std::cerr << "¡Registro inexistente!" << std::endl;
            instruction::correct_ = false;
            return 0;
        }
        return instruction::operand_.cut(1,instruction::operand_.size()-1).toInt();
    //hay que coger el valor de un registro
    }else{
        if (instruction::operand_.toInt() <= 0) {
            std::cerr << "¡Registro inexistente!" << std::endl;
            instruction::correct_ = false;
            return 0;
        }
        valueOperand = mathInstruction::registros_->operator[](instruction::operand_.toInt());
    }
    return *mathInstruction::acumulador_ + valueOperand;
}