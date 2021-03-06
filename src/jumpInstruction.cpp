#include "../include/jumpInstruction.hpp"

void jumpInstruction::stablishAcumulador(int* pointer) {
    acumulador_ = pointer;
}

void jumpInstruction::stablishEtiquetas(std::unordered_map<std::string,unsigned>* pointer){
    etiquetasInstruccion_ = pointer;
}
