#include "../include/RAMMachine.hpp"

RAMMachine::RAMMachine(const std::string& entrada, const std::string& salida,
                        const std::string& programa, const bool& modo): programa_(programa){
    ficheroSalida_ = salida;
    debug_ = modo;//true debug false normal
    programCounter_ = 0;
    acumulador_ = 0;
    instruccionesEjecutadas_ = 0;
    state_ = false;

    std::vector<int> entradaLeida;
    std::fstream file(entrada);
    if (file.is_open()) {
        bool correct = true;
        std::string line;
        while (getline(file,line)) {
            for (size_t i = 0; i < line.size(); i++) {
                if (line[i] != ' ') {
                    int number = (int)line[i]-48;
                    if ( number < 0) {
                        std::cerr << "Error en la entrada" << std::endl;
                    }else{
                        entradaLeida.push_back(number);
                    }
                }
            }
        }
        file.close();
        cintaEntrada_.setCinta(entradaLeida);
        registros_.set({0,0,0,0,0});
        setPointers();
    }else{
        std::cerr << "Error, fichero " << entrada << " no se ha podido leer" << std::endl;
    }
}

void RAMMachine::show(void)const{
    showState();
    showPrograma();
}


void RAMMachine::showState(void)const{
    std::cout << "Estado actual: " << (state_ ? "Activo" : "HALT") << std::endl;
    std::cout << "Modo Debug: " << (debug_ ? "Activado" : "Desactivado") << std::endl;
    std::cout << "Acumulador: " << acumulador_ << std::endl;
    std::cout << "Contador de Programa: " << programCounter_ << std::endl;
    showCintaEntrada();
    std::cout << std::endl;
    showCintaSalida();
    std::cout << std::endl;
    showRegisters();
}

void RAMMachine::showRegisters(void)const{
    std::cout << "Estado actual de los registros:" << std::endl;
    for (size_t i = 0; i < registros_.size(); i++) {
        std::cout << " R[" << i << "] = " << registros_[i] << std::endl;
    }
    std::cout << "El número de registros es dinámicamente modificado, es decir";
    std::cout << ", cuando hace falta uno más, se crea" << std::endl;
}

void RAMMachine::showCintaEntrada(void)const{
    std::cout << "Cinta Entrada: ";
    cintaEntrada_.show();
}

void RAMMachine::showCintaSalida(void)const{
    std::cout << "Cinta Salida: ";
    cintaSalida_.show();
}


void RAMMachine::showPrograma(void)const{
    std::cout << "Programa Cargado: " << std::endl;
    programa_.showProgram();
}

void RAMMachine::setPointers(void){
    for (size_t i = 0; i < programa_.size(); i++){
        if ( programa_[i]->kindOf() == myString("math") ) {
            programa_[i]->stablishAcumulador(&acumulador_);
            programa_[i]->stablishRegistros(&registros_);
        }else if ( programa_[i]->kindOf() == myString("jump") ) {
            programa_[i]->stablishAcumulador(&acumulador_);
            programa_[i]->stablishEtiquetas(programa_.getEtiquetas());
        }else if ( programa_[i]->kindOf() == myString("registry") ) {
            programa_[i]->stablishAcumulador(&acumulador_);
            programa_[i]->stablishRegistros(&registros_);
        }
    }
}

void RAMMachine::execute(void){
    state_ = true;
    bool correct = true;
    //mientras que el estado sea running y no haya errores
    while (state_ && correct) {
        //check que no te pasas del tamaño del programa
        if (programCounter_ >= programa_.size()) {
            std::cerr << "¡El programa ha terminado y la máquina sigue ejecutando!" << std::endl;
            std::cerr << "Quizás falte una instrucción halt..." << std::endl;
            state_ = false;
            correct = false;
            break;
        }
        
        instruction* instruccionActiva = programa_[programCounter_];

        if (instruccionActiva->kindOf() == myString("math")) {
            acumulador_ = instruccionActiva->apply();
            if(!instruccionActiva->isCorrect()){
                std::cerr << "Error se divide entre 0!" << std::endl;
                instruccionActiva->show();
                state_ = false;
                correct = false;
            }
        }else if (instruccionActiva->kindOf() == myString("jump")) {
            int toJump = instruccionActiva->apply();
            if (toJump == -1) {
                std::cerr << "Error en instruccion de salto!" << std::endl;
                instruccionActiva->show();
                state_ = false;
                correct = false;
            }else{
                programCounter_ = toJump;
            }
        }else if (instruccionActiva->kindOf() == myString("registry")) {
            instruccionActiva->apply();
        }else if (instruccionActiva->kindOf() == myString("memory")) {
            if (instruccionActiva->name() == myString("read")){
                if ( instruccionActiva->indirectMode() ){
                    registros_[instruccionActiva->solveIndirection()] = cintaEntrada_.read(); 
                }else{
                    registros_[instruccionActiva->apply()] = cintaEntrada_.read();
                }
            }else{
                cintaSalida_.write(registros_[instruccionActiva->apply()]);
            }
        }else if (instruccionActiva->kindOf() == myString("halt")) {
            instruccionesEjecutadas_++;
            state_ = false;
            correct = true;
        }
        
        instruccionesEjecutadas_++;
        //las instrucciones de salto ya dejan el PC en el numero correcto
        if (!(instruccionActiva->kindOf() == myString("jump"))) {
            programCounter_++;
        }
        showState();
        int a;
        std::cin >> a;
    }

    if (correct) {
        cintaSalida_.toFile(ficheroSalida_);
    }
}

void RAMMachine::executeStepByStep(void){
    state_ = true;
    bool correct = true;
    //mientras que el estado sea running y no haya errores
    while (state_ && correct) {
        //check que no te pasas del tamaño del programa
        if (programCounter_ >= programa_.size()) {
            std::cerr << "¡El programa ha terminado y la máquina sigue ejecutando!" << std::endl;
            std::cerr << "Quizás falte una instrucción halt..." << std::endl;
            state_ = false;
            correct = false;
        }
        
        instruction* instruccionActiva = programa_[programCounter_];

        if (instruccionActiva->kindOf() == myString("math")) {
            acumulador_ = instruccionActiva->apply();
            if(!instruccionActiva->isCorrect()){
                std::cerr << "Error se divide entre 0!" << std::endl;
                instruccionActiva->show();
                state_ = false;
                correct = false;
            }
        }else if (instruccionActiva->kindOf() == myString("jump")) {
            int toJump = instruccionActiva->apply();
            if (toJump == -1) {
                std::cerr << "Error en instruccion de salto!" << std::endl;
                instruccionActiva->show();
                state_ = false;
                correct = false;
            }else{
                programCounter_ = toJump;
            }
        }else if (instruccionActiva->kindOf() == myString("registry")) {
            instruccionActiva->apply();
        }else if (instruccionActiva->kindOf() == myString("memory")) {
            if (instruccionActiva->name() == myString("read")){
                if ( instruccionActiva->indirectMode() ){
                    registros_[instruccionActiva->solveIndirection()] = cintaEntrada_.read(); 
                }else{
                    registros_[instruccionActiva->apply()] = cintaEntrada_.read();
                }
            }else{
                cintaSalida_.write(registros_[instruccionActiva->apply()]);
            }
        }else if (instruccionActiva->kindOf() == myString("halt")) {
            instruccionesEjecutadas_++;
            state_ = false;
            correct = true;
        }
        
        instruccionesEjecutadas_++;
        //las instrucciones de salto ya dejan el PC en el numero correcto
        if (!(instruccionActiva->kindOf() == myString("jump"))) {
            programCounter_++;
        }
        showState();
        int a;
        std::cin >> a;
    }

    if (correct) {
        cintaSalida_.toFile(ficheroSalida_);
    }
}
