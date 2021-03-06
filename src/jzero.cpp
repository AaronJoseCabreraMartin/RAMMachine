#include "../include/jzero.hpp"

int jzero::apply(void){
    //si no hay que saltar devuelve -1
    //si hay que saltar devolvera el numero
    //que debe colarse en el PC [0...n] (n instrucciones)
    int toReturn = -1;
    if(*acumulador_ == 0){
       toReturn = jumpInstruction::etiquetasInstruccion_->operator[](instruction::operand_);
    }
    return toReturn;
}
