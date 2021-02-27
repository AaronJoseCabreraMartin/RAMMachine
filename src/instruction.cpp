#include "../include/instruction.hpp"

instruction::instruction(const myString& instruccion){
    clear();
    std::string tag;
    std::string instructionAndOperand;
    hasTag_ = false;
    for (size_t i = 0; i < instruccion.size(); i++){
        if (instruccion[i] == ':') {
            hasTag_ = true;
        }
    }
    bool tagPassed;
    
    if (hasTag_){
        tagPassed = false;
    }else{
        tagPassed = true;
    }

    for (size_t i = 0; i < instruccion.size(); i++) {
        if (tagPassed) {
            //si ya pasamos la tag lo que queda es instruccion
            instructionAndOperand.push_back(instruccion[i]);
        }else{
            //sino, almacenamos los caracteres como tag
            if (instruccion[i]==':') {
                tagPassed = true;
            }else{
                tag.push_back(instruccion[i]);
            }
        }  
    }
    std::string clearedInstruction;
    bool foundCharacter = false;
    for (int i = 0; i < instructionAndOperand.size(); i++){
        //el primer caracter es una letra mayuscula/minuscula
        if ( ( (int) instructionAndOperand[i] > 64 && (int) instructionAndOperand[i] < 91 ) || 
            ( (int) instructionAndOperand[i] > 96 && (int) instructionAndOperand[i] < 123 ) ) {
            clearedInstruction.push_back(instructionAndOperand[i]);
            foundCharacter=true;
        }else if(foundCharacter){
            //sino es un numero ni una letra le hago push si ya habia encontrado un caracter
            clearedInstruction.push_back(instructionAndOperand[i]);
        }
    }
    bool foundSeparator = false;
    std::string operando, onlyIntruction;
    for (size_t i = 0; i < clearedInstruction.size(); i++) {
        if (foundSeparator && clearedInstruction[i] != ' ' &&
                    clearedInstruction[i] != '\t' && 
                    clearedInstruction[i] != '	') {
            operando.push_back(clearedInstruction[i]);
        }else{
            //los operandos siempre vienen separados por un espacio
            if (clearedInstruction[i] == ' ') {
                foundSeparator = true;
            }else{
                onlyIntruction.push_back(clearedInstruction[i]);
            }
        }
    }

    // si se encontro operando, el tamaño no sera 0
    hasOperand_ = operando.size() != 0;

    tag_.set(tag);
    instruction_.set(myString(onlyIntruction).capitalize().string());
    operand_.set(operando);
}

void instruction::show(void)const{
    if (hasTag_) {
        std::cout << tag_.string() << ": ";
    }
    std::cout << instruction_.string();

    if (hasOperand_) {
        std::cout << " " << operand_.string();
    }

    std::cout << std::endl;
}

void instruction::clear(void){
    instruction_.clear();
    hasTag_ = false;
    tag_.clear();
    hasOperand_ = false;
    operand_.clear();
}
