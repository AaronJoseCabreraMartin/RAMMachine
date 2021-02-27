#include "../include/instruction.hpp"

instruction::instruction(const myString& instruccion){
    std::string tag;
    std::string realinstruction;
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
            realinstruction.push_back(instruccion[i]);
        }else{
            //sino, almacenamos los caracteres como tag
            if (instruccion[i]==':') {
                tagPassed = true;
            }else{
                tag.push_back(instruccion[i]);
            }
        }  
    }
    std::string noSpaceInstruction;
    bool foundCharacter = false;
    for (int i = 0; i < realinstruction.size(); i++){
        //es un numero o es una letra mayuscula/minuscula
        if ( ( (int) realinstruction[i] > 47 && (int) realinstruction[i] < 58 ) ||
            ( (int) realinstruction[i] > 64 && (int) realinstruction[i] < 91 ) || 
            ( (int) realinstruction[i] > 96 && (int) realinstruction[i] < 123 ) ) {
            noSpaceInstruction.push_back(realinstruction[i]);
            foundCharacter=true;
        }else if(foundCharacter){
            //sino es un numero ni una letra le hago push si ya habia encontrado un caracter
            noSpaceInstruction.push_back(realinstruction[i]);
        }
    }
    instruction_.set(noSpaceInstruction);
    tag_.set(tag);
}

void instruction::show(void)const{
    if (hasTag_) {
        std::cout << tag_.string() << ": "<< std::endl;
    }
    std::cout << instruction_.string() << std::endl;
}
