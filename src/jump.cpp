#include "../include/jump.hpp"

int jump::apply(void){
    return jumpInstruction::etiquetasInstruccion_->operator[](instruction::operand_);
}
