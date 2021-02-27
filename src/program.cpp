#include "../include/program.hpp"

program::program(const std::string& ficheroPrograma){

    buildInstructions();
    std::fstream file(ficheroPrograma);
    if (file.is_open()) {
        bool correct = true;
        std::string line;
        char caracter;
        while( !file.eof() ) {
            file.get(caracter);
            if (caracter != '\n') {
                if (line.size() == 0 && caracter != '\t' && caracter != ' ' 
                        && caracter != '	' && caracter != '\n') {
                    line.push_back(caracter);
                }else if (line.size() != 0 && caracter != '\n') {
                    if (caracter == '\t' || caracter == '	'){
                        caracter = ' ';
                    }
                    line.push_back(caracter);
                }
            }else{
                std::cout << line << std::endl;
                myString fixedLine = deleteComments(line);
                std::cout << fixedLine.string() << " Size:" << fixedLine.size() << std::endl;

                if (fixedLine.size() > 1 && checkLineSyntax(fixedLine)) {
                    program_.push_back(instruction(fixedLine));
                }else if (fixedLine.size() > 1) {
                    std::cout << program_.size()+1 << std::endl;
                    std::cerr << "Fallo sintactico en: " << fixedLine.string() << std::endl;
                    std::cerr << "Linea: " << program_.size()+1 << std::endl;
                    correct = false;
                    line.clear();
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
                std::cerr << "Fallo sintactico en \"" << fixedLine.string() << "\" linea: " << program_.size()+1 << std::endl;
                correct = false;
            }
        }

        buildTaggedInstructions();
        if (correct) {
            // 0 correcto
            int errorSemantico = checkSemantic();
            if (errorSemantico == 1) {
                std::cerr << "Error se salta a una etiqueta no definida" << std::endl;
            }else if (errorSemantico == 2) {
                std::cerr << "Error etiqueta duplicada" << std::endl;
            }else if (errorSemantico == 3) {
                // unico caso DIV =0
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
        if (program_[i].hasTag()) {
            std::cout << " Etiqueta: " << program_[i].getTag().string();
        }else{
            std::cout << '\t' << '\t';
        }

        std::cout << " Instruccion: " << program_[i].getInstruction().string();

        if (program_[i].hasOperand()) {
            std::cout << " Operando: " << program_[i].getOperand().string();
        }
        
        std::cout << std::endl;
    }
}

bool program::checkLineSyntax(const myString& line)const{
    instruction instructionargumentToCheck(line);
    //comprobamos si tiene operando y si es una de las instrucciones
    if (instructionargumentToCheck.hasOperand() && isAnInstruction(instructionargumentToCheck.getInstruction())) {
        //comprobamos que el operando sea sintacticamente correcto
        return correctArgument(instructionargumentToCheck);
    }else if (!instructionargumentToCheck.hasOperand()) {
        //si no tiene operando, DEBE ser HALT
        return instructionargumentToCheck.getInstruction() == allowedInstructions_[11];
    }

    return false;
}

int program::checkSemantic(void)const{
    int error = 0;
    for (size_t i = 0; i < program_.size(); i++) {
        if (isAJumpInstruction(program_[i].getInstruction())) {
            //si hay etiquetas duplicadas
            if (!checkDoubleTags()){
                error = 2;
                break;
            //o si la etiqueta no existe
            }else if(!checkTagDefined(program_[i].getOperand())) {
                error = 1;
                break;
            }
            //si es DIV
            //comprobar que no divida entre 0 o entre -0  
        }else if (program_[i].getInstruction() == allowedInstructions_[5] && 
                    (program_[i].getOperand() == myString("0") || 
                    program_[i].getOperand() == myString("-0"))) {
            error = 3;
            break;
        }
    }
    return error;
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

    jumpInstructions_ = {
                //JUMP JGTZ JZERO 
                allowedInstructions_[8], 
                allowedInstructions_[9],
                allowedInstructions_[10]
                };

     indirectInstructons_ = {
                //STORE READ
                allowedInstructions_[1],
                allowedInstructions_[6]
                };
}

bool program::isAnInstruction(const myString& argumentToCheck)const{
    myString argumentToCheckCapitalized(argumentToCheck.capitalize());
    bool found = false;
    for (size_t i = 0; i < allowedInstructions_.size(); i++) {
        if (allowedInstructions_[i] == argumentToCheckCapitalized) {
            found = true;
            break;
        }
    }
    return found;
}

bool program::correctArgument(const instruction& sentenceToCheck)const{
    //si llega aqui no es HALT
    std::string argumentToCheck = sentenceToCheck.getOperand();
    //debe tener argumento
    if (argumentToCheck.size() == 0) {
        return false;
    }
    
    if (isAJumpInstruction(sentenceToCheck.getInstruction())) {
        //si hubiera algo que en una etiqueta no deberia aparecer
    }else if (isAnIndirectInstruction(sentenceToCheck.getInstruction())
                && argumentToCheck[0] == '*'  ) {
        //*numero ni el registro ni lo que contiene el registro puede ser negativo
        for (size_t i = 1; i < argumentToCheck.size(); i++) {
            //si no es un numero, mal
            if ( !((int) argumentToCheck[i] > 47 && (int) argumentToCheck[i] < 58) ){
                return false;
            }
        }
        //LAS INSTRUCCIONES INDIRECTAS NO PUEDEN VENIR CON UN =
    }else if (isAnIndirectInstruction(sentenceToCheck.getInstruction())
                && argumentToCheck[0] == '='  ) {
        return false;
    }else{
        //NO ES UNA INSTRUCCION DE SALTO NI DE INDIRECCION
        //y si es de indireccion no tiene un =

        //=numero (literales) pueden ser negativos
        if (argumentToCheck[0] == '=') {
            // seria ADD = 
            // (no se permite se necesita un numero)
            if (argumentToCheck.size() == 1) {
                return false;
            }
            //si es un numero negativo salta el signo
            int start = argumentToCheck[1] == '-' ? 2 : 1;
            for (size_t i = start; i < argumentToCheck.size(); i++) {
                //si no es un numero, mal
                if ( !((int) argumentToCheck[i] > 47 && (int) argumentToCheck[i] < 58) ){
                    return false;
                }
            }
        //numeros (registros) NO PUEDEN SER NEGATIVOS
        }else{
                std::cout << argumentToCheck << " " << argumentToCheck.size() << std::endl;
            for (size_t i = 0; i < argumentToCheck.size(); i++) {
                //si no es un numero, mal
                if ( !((int) argumentToCheck[i] > 47 && (int) argumentToCheck[i] < 58) ){
                    return false;
                }
            }
        }
    }
    
    //supongo que no permitimos indireccion multiple **1 o *******1
    
    return true;
}


void program::buildTaggedInstructions(void){
    taggedLines_.clear();
    for (size_t i = 0; i < program_.size(); i++) {
        if (program_[i].hasTag()) {
            taggedLines_.push_back(std::pair<myString,unsigned>(program_[i].getTag(),i));
        }
    }
}

bool program::checkDoubleTags(void)const{
    for (size_t i = 0; i < taggedLines_.size(); i++) {
        for (size_t j = 0; j < taggedLines_.size(); j++) {
            if ( i!=j && taggedLines_[i].first == taggedLines_[j].first ){
                return false;
            }
        }
    }
    return true;
}

bool program::isAJumpInstruction(const myString& instruction)const{
    for (size_t i = 0; i < jumpInstructions_.size(); i++) {
        if (jumpInstructions_[i] == instruction) {
            return true;
        }
    }
    return false;
}

bool program::checkTagDefined(const myString& tag)const{
    for (size_t i = 0; i < taggedLines_.size(); i++) {
        if (taggedLines_[i].first == tag) {
            return true;
        }
    }
    return false;
}

bool program::isAnIndirectInstruction(const myString& instruction)const{
    for (size_t i = 0; i < indirectInstructons_.size(); i++) {
        if (indirectInstructons_[i] == instruction){
            return true;
        }
    }
    return false;
}
