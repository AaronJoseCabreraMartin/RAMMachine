#include "../include/program.hpp"

program::program(const std::string& ficheroPrograma){

    buildInstructions();
    std::fstream file(ficheroPrograma);
    if (file.is_open()) {
        bool correct = true;
        std::string line;
        char caracter;
        while( !file.eof() && file.get(caracter) ) {
            if (caracter != '\n') {
                if (line.size() == 0 && caracter != '\t' && caracter != ' ' && caracter != '	') {
                    line.push_back(caracter);
                }else if (line.size() != 0) {
                    if (caracter == '\t' && caracter == '	'){
                        caracter = ' ';
                    }
                    line.push_back(caracter);
                }
            }else{
                myString fixedLine = deleteComments(line);
                if (fixedLine.size() != 0 && checkLineSyntax(fixedLine)) {
                    instruction instruccion(fixedLine);
                    program_.push_back(instruccion);
                }else if (fixedLine.size() != 0) {
                    std::cerr << "Fallo sintactico en " << fixedLine.string() << " linea: " << program_.size()+1 << std::endl;
                    correct = false;
                    break;
                }
                line.clear();
            }
        }
        
        if (line.size() != 0) {
            myString fixedLine = deleteComments(line);
            if (fixedLine.size() != 0 && checkLineSyntax(fixedLine)) {
                instruction instruccion(fixedLine);
                program_.push_back(instruccion);
            }else if (fixedLine.size() != 0) {
                std::cerr << "Fallo sintactico en " << fixedLine.string() << " linea: " << program_.size()+1 << std::endl;
                correct = false;
            }
        }

        if (!correct) {
            // 0 correcto
            int errorSemantico = checkSemantic();
            if (errorSemantico == 1) {
                std::cerr << "Se salta a una etiqueta no definida" << std::endl;
            }else if (errorSemantico == 2) {
                // unico caso DIV=0
                std::cerr << "Se divide entre 0" << std::endl;
            }
        }
        file.close();
    }else{
        std::cerr << "Error, fichero " << ficheroPrograma << " no se puede abrir" << std::endl;
    }
}

void program::showProgram(void)const{
    for (size_t i = 0; i < program_.size(); i++) {
        std::cout << "Linea: " << i;
        if (program_[i].hasTag()){
            std::cout << " Tag: " << program_[i].getTag().string();
        }else{
            std::cout << '\t';
        }
        std::cout << " Instruction: " << program_[i].getInstruction().string() << std::endl;
    }
}

bool program::checkLineSyntax(const myString& line)const{
    //debe ser 
    // INSTRUCCION OPERANDO 
    // (sino tiene operando solo es correcto si es HALT)
    // ETIQUETA INSTRUCCION OPERANDO
    // ademas la instruccion debe estar en allowedInstructions_
    return true;
}

int program::checkSemantic(void)const{
    //revisar la semantica entera del programa
    // siempre que se salta, es a una etiqueta que existe
    // no se divide entre 0
    return 0;
}


myString program::deleteComments(const myString& line)const{
    std::string noComments;
    unsigned index = 0;
    while (index < line.size() && line[index] != '#') {
        noComments.push_back(line[index]);
        index++;
    }
    return myString(noComments);
}

void program::buildInstructions(void){
    allowedInstructions_ = {
                myString("LOAD"), myString("STORE"), myString("ADD"), 
                myString("SUB"), myString("MULT"), myString("DIV"), 
                myString("READ"), myString("WRITE"), myString("JUMP"), 
                myString("JGTZ"), myString("JZERO"), myString("HALT")
                };
}