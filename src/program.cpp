#include "../include/program.hpp"

program::program(const std::string& ficheroPrograma){
    duplicateTags_ = false;
    comments_ = ';';
    buildInstructions();

    std::fstream file(ficheroPrograma);
    if (file.is_open()) {
        bool correct = true;
        std::string line;
        char caracter;
        while( !file.eof() && file.get(caracter) ) {
            if (caracter != '\n') {
                if (line.size() == 0 && caracter != '\t' && caracter != ' ' 
                        && caracter != '	' && caracter != '\n' 
                        && (int)caracter != 13 ) {
                    line.push_back(caracter);
                }else if (line.size() != 0 && caracter != '\n' && 
                            (int)caracter != 13) {
                    if (caracter == '\t' || caracter == '	'){
                        caracter = ' ';
                    }
                    line.push_back(caracter);
                }
            }else{
                
                myString fixedLine = deleteComments(line);
                fixedLine = deleteInnerSpaces(fixedLine);
                if (fixedLine.size() > 1 && checkLineSyntax(fixedLine)) {
                    program_.push_back(createInstruction(fixedLine));
                }else if (fixedLine.size() > 1) {
                    std::cerr << "Fallo sintactico en: \"" << fixedLine.string() << "\""<< std::endl;
                    correct = false;
                    line.clear();
                    clear();
                    return;
                }
                line.clear();
            }
        }
        
        if (line.size() != 0) {
            myString fixedLine = deleteComments(line);
            fixedLine = deleteInnerSpaces(line);
            if (fixedLine.size() > 1 && checkLineSyntax(fixedLine)) {
                program_.push_back(createInstruction(fixedLine));
            }else if (fixedLine.size() > 1) {
                std::cerr << "Fallo sintactico en: \"" << fixedLine.string() << "\""<< std::endl;
                correct = false;
                line.clear();
                clear();
                return;
            }
        }

        buildTaggedInstructions();
        if (correct) {
            // 0 correcto
            int errorSemantico = checkSemantic();
            char error;
            if (errorSemantico == 1) {
                std::cerr << "Error se salta a una etiqueta no definida" << std::endl;
                std::cin >> error;
                clear();
            }else if (errorSemantico == 2) {
                std::cerr << "Error etiqueta duplicada" << std::endl;
                std::cin >> error;
                clear();
            }else if (errorSemantico == 3) {
                // unico caso DIV =0
                std::cerr << "Error, se divide entre 0: DIV =0" << std::endl;
                std::cin >> error;
                clear();
            }
        }
        file.close();
    }else{
        std::cerr << "Error, fichero " << ficheroPrograma << " no se puede abrir" << std::endl;
    }
}

program::~program(){
    for (size_t i = 0; i < program_.size(); i++) {
        delete program_[i];
    }
    program_.clear();
}


//la linea no tiene comentarios (falta mayuscula, no puedo por etiqueta) 
instruction* program::createInstruction(const myString& line)const{
    //comparo con la mayus pero creo con la minus
    myString capitalizedLine = line.capitalize();
    if (capitalizedLine.contains(allowedInstructions_[11])) {
        return new halt(line);
    }else if (capitalizedLine.contains(allowedInstructions_[0])) {
        return new load(line);
    }else if (capitalizedLine.contains(allowedInstructions_[1])) {
        return new store(line);
    }else if (capitalizedLine.contains(allowedInstructions_[2])) {
        return new add(line);
    }else if (capitalizedLine.contains(allowedInstructions_[3])) {
        return new sub(line);
    }else if (capitalizedLine.contains(allowedInstructions_[4]) || 
                capitalizedLine.contains(allowedInstructions_[12])) {
        return new mult(line);
    }else if (capitalizedLine.contains(allowedInstructions_[5])) {
        return new Div(line);
    }else if (capitalizedLine.contains(allowedInstructions_[6])) {
        return new read(line);
    }else if (capitalizedLine.contains(allowedInstructions_[7])) {
        return new write(line);
    }else if (capitalizedLine.contains(allowedInstructions_[8])) {
        return new jump(line);
    }else if (capitalizedLine.contains(allowedInstructions_[9])) {
        return new jgtz(line);
    }else if (capitalizedLine.contains(allowedInstructions_[10])) {
        return new jzero(line);
    }
    std::cerr << "Lectura incorrecta de instruciones, instruccion ";
    std::cerr << line.string() << " sustituida por HALT" << std::endl;
    return new halt(line);
}


void program::showProgram(void)const{
    for (size_t i = 0; i < program_.size(); i++) {
        std::cout << "Linea: " << i;
        if (program_[i]->hasTag()) {
            std::cout << " Etiqueta: " << program_[i]->getTag().string();
        }else{
            std::cout << '\t' << '\t';
        }

        std::cout << " Instruccion: " << program_[i]->getInstruction().string();

        // si no es halt tiene operando
        if (!(program_[i]->kindOf() == allowedInstructions_[11])) {
            std::cout << " Operando: " << program_[i]->getOperand().string();
        }
        
        std::cout << std::endl;
    }
}

bool program::checkLineSyntax(const myString& line)const{

    std::vector<myString> instructionsParts = splitInstructionParts(line);
    // 0 etiqueta (si tiene sino, vacia)
    // 1 instruccion
    // 2 argumento
    if ( instructionsParts[0].size() != 0 ) {
        for (size_t i = 0; i < instructionsParts[0].size(); i++) {
            if ( instructionsParts[0][i] == comments_) {
                return false;
            }
        }
    }
    
    if ( instructionsParts[1] == myString("HALT") ) {
        // si es halt y no tiene argumentos esta OK, sino no
        return instructionsParts[2].size() == 0;
    }

    instruction* instructionToCheck; 
    if (instructionsParts[1] == allowedInstructions_[0]) {
        instructionToCheck = new load(line);
    }else if (instructionsParts[1] == allowedInstructions_[1]) {
        instructionToCheck = new store(line);
    }else if (instructionsParts[1] == allowedInstructions_[2]) {
        instructionToCheck = new add(line);
    }else if (instructionsParts[1] == allowedInstructions_[3]) {
        instructionToCheck = new sub(line);
    }else if (instructionsParts[1] == allowedInstructions_[4] || 
                instructionsParts[1] == allowedInstructions_[12]) {
        instructionToCheck = new mult(line);
    }else if (instructionsParts[1] == allowedInstructions_[5]) {
        instructionToCheck = new Div(line);
    }else if (instructionsParts[1] == allowedInstructions_[6]) {
        instructionToCheck = new read(line);
    }else if (instructionsParts[1] == allowedInstructions_[7]) {
        instructionToCheck = new write(line);
    }else if (instructionsParts[1] == allowedInstructions_[8]) {
        instructionToCheck = new jump(line);
    }else if (instructionsParts[1] == allowedInstructions_[9]) {
        instructionToCheck = new jgtz(line);
    }else if (instructionsParts[1] == allowedInstructions_[10]) {
        instructionToCheck = new jzero(line);
    }else{
        //si no es ninguna de esas instrucciones esta mal
        return false;
    }

    return correctArgument(instructionToCheck);
}

std::vector<myString> program::splitInstructionParts(const myString& line)const{
    std::vector<myString> toReturn;
    toReturn.resize(3);
    int i = 0;
    //tiene etiqueta
    if ( line.contains(myString(":")) ) {
        std::string etiqueta;
        while ( line[i] != ':' ){
            etiqueta.push_back(line[i]);
            i++;
        }
        toReturn[0] = myString(etiqueta).capitalize();
        i++;// :
        i++;
    }

    //evitamos hasta llegar a un caracter que no sea en blanco
    while ( i < line.size() && (line[i] == '\t' || line[i] == ' ' 
            || line[i] == '	' || line[i] == '\n' || (int)line[i] == 13)){
        i++;
    }
    
    
    std::string instruccion;
    while ( i < line.size() && line[i] != ' ' ) {
        instruccion.push_back(line[i]);
        i++;
    }
    toReturn[1] = myString(instruccion).capitalize();

    std::string argumento;
    while ( i < line.size() ) {
        argumento.push_back(line[i]);
        i++;
    }
    //toReturn[2] = myString(argumento).capitalize();
    toReturn[2] = myString(argumento);
    return toReturn;
}


int program::checkSemantic(void){
    int error = 0;
    for (size_t i = 0; i < program_.size(); i++) {
        //if (isAJumpInstruction(program_[i].getInstruction())) {
        if (program_[i]->kindOf() == myString("jump")){
            //si hay etiquetas duplicadas
            if (duplicateTags_){
                error = 2;
                break;
            //o si la etiqueta no existe
            }else if(!checkTagDefined(program_[i]->getOperand())) {
                error = 1;
                break;
            }
            //si es DIV
            //comprobar que no divida entre 0 o entre -0  
        }else if (program_[i]->getInstruction() == allowedInstructions_[5] && 
                    (program_[i]->getOperand() == myString("=0") || 
                    program_[i]->getOperand() == myString("=-0"))) {
            error = 3;
            break;
        }
    }
    return error;
}


myString program::deleteComments(const myString& line)const{
    std::string noComments;
    unsigned index = 0;
    while (index < line.size() && line[index] != comments_) {
        noComments.push_back(line[index]);
        index++;
    }
    return myString(noComments);
}

void program::buildInstructions(void){
    allowedInstructions_ = {
                myString("LOAD"), myString("STORE"), myString("ADD"), 
                myString("SUB"), myString("MUL"), myString("DIV"), 
                myString("READ"), myString("WRITE"), myString("JUMP"), 
                myString("JGTZ"), myString("JZERO"), myString("HALT"),
                myString("MULT") // en algunos ficheros se usa mult
                };
}

bool program::correctArgument(const instruction* sentenceToCheck)const{
    //si llega aqui no es HALT
    std::string argumentToCheck = sentenceToCheck->getOperand();
    //debe tener argumento
    if (argumentToCheck.size() == 0) {
        return false;
    }
    
    if (sentenceToCheck->kindOf() == myString("jump")) {
        //si hubiera algo que en una etiqueta no deberia aparecer
    //esta en modo indirecto y es una instruccion indirecta
    }else if (sentenceToCheck->indirect()
                && argumentToCheck[0] == '*'  ) {
        //despues de la primera posicion si pueden venir 0 (48 es el 0)
        if ( !((int) argumentToCheck[1] > 48 && (int) argumentToCheck[1] < 58) ){
                return false;
        }
        //*numero ni el registro ni lo que contiene el registro puede ser negativo
        for (size_t i = 2; i < argumentToCheck.size(); i++) {
            //si no es un numero, mal (48 es el 0)
            if ( !((int) argumentToCheck[i] > 47 && (int) argumentToCheck[i] < 58) ){
                return false;
            }
        }
    //LAS INSTRUCCIONES STORE Y LOAD NO PUEDEN VENIR CON UN =
    }else if ( !sentenceToCheck->inmediateAllowed() && argumentToCheck[0] == '=') {
        return false;
    }else{
        //NO ES UNA INSTRUCCION DE SALTO NI ESTA EN MODO INDIRECTO
        //y si es store y load no tiene un =

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
                //si no es un numero, mal (0 permitido)
                if ( !((int) argumentToCheck[i] > 47 && (int) argumentToCheck[i] < 58) ){
                    return false;
                }
            }
        //numeros (registros) NO PUEDEN SER NEGATIVOS NI 0
        }else{
            //despues de la primera posicion si pueden venir 0 (48 es el 0)
            if ( !((int) argumentToCheck[0] > 48 && (int) argumentToCheck[0] < 58) ){
                    return false;
            }
            for (size_t i = 1; i < argumentToCheck.size(); i++) {
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
    int numberOfTags = 0;
    for (size_t i = 0; i < program_.size(); i++) {
        if (program_[i]->hasTag()) {
            //taggedLines_.push_back(std::pair<myString,unsigned>(program_[i]->getTag(),i));
            taggedLines_[program_[i]->getTag().string()] = i;
            numberOfTags++;
        }
    }
    // si el número de tags que hemos introducido no es
    // el mismo que el numero de tags que tiene el hash
    // es que hay alguna repetida
    duplicateTags_ = numberOfTags != taggedLines_.size();
}

bool program::checkTagDefined(const myString& tag){
    std::unordered_map<std::string,unsigned>::iterator got;
    got = taggedLines_.find (tag.string());
    //si es el end, es que no estaba
    return !(got == taggedLines_.end());
}

void program::clear(void){
    taggedLines_.clear();
    for (size_t i = 0; i < program_.size(); i++) {
        delete program_[i];
    }
    program_.clear();
}

myString program::deleteInnerSpaces(const myString& line)const{
    std::string toReturn;
    int i = 0;
    if ( line.contains(myString(":")) ){
        while ( line[i] != ':' ){
            if ( line[i] != '\t' && line[i] != ' ' && line[i] != '	' 
                    && line[i] != '\n' && (int)line[i] != 13 ) {
                toReturn.push_back(line[i]);
            }
            i++;
        }
        toReturn.push_back(line[i]);
        i++;
    }
    //avanzamos hasta encontrar un caracter que no sea espacio
    while ( i < line.size() && (line[i] == '\t' || line[i] == ' ' 
            || line[i] == '	' || line[i] == '\n' || (int)line[i] == 13) ) {
        i++;
    }
    if ( toReturn.size() != 0 ){
        toReturn.push_back(' ');
    }
    

    bool spaceAdded = false;
    while (i < line.size()) {
        //si no he añadido un espacio y encuentro uno lo añado
        if (!spaceAdded && (line[i] == '\t' || line[i] == ' ' || line[i] == '	' 
                    || line[i] == '\n' || (int)line[i] == 13)) {
            spaceAdded = true;
            toReturn.push_back(' ');
        //si no es un espacio lo añado
        }else if (line[i] != '\t' && line[i] != ' ' && line[i] != '	' 
                    && line[i] != '\n' && (int)line[i] != 13) {
            toReturn.push_back(line[i]);
        }
        i++;
    }
    return myString(toReturn);
}

std::unordered_map<std::string,unsigned>* program::getEtiquetas(void){
    return &taggedLines_;
}
