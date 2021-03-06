#include "../include/add.hpp"

int add::apply(void){
    int valueOperand;
    if ( instruction::operand_.contains(myString("=")) ) {
        valueOperand = instruction::operand_.cut(1,instruction::operand_.size()-1).toInt();
    //si no es carga directa, se coge el valor desde un registro
    } else {
        valueOperand = mathInstruction::registros_->operator[](instruction::operand_.toInt());
    }
    return *mathInstruction::acumulador_ + valueOperand;
}