#include "../include/div.hpp"

int Div::apply(void){
    int valueOperand;
    if ( instruction::operand_.contains(myString("=")) ) {
        valueOperand = instruction::operand_.cut(1,instruction::operand_.size()-1).toInt();
    //si no es carga directa, se coge el valor desde un registro
    } else {
        valueOperand = mathInstruction::registros_->operator[](instruction::operand_.toInt());
    }
    if (valueOperand == 0){
        std::cerr << "¡Error! ¡Division por 0!" << std::endl;
        //*state_ = false;
        instruction::correct_ = false;
        return 0;
    }
    
    return (*mathInstruction::acumulador_) / valueOperand;
}