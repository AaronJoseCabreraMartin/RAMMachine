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
    entradaLeida.push_back(0);
    std::fstream file(entrada);
    if (file.is_open()) {
        bool correct = true;
        std::string line;
        while (getline(file,line)) {
            std::string number;
            for (size_t i = 0; i < line.size(); i++) {
                if (line[i] != ' ') {
                    number.push_back(line[i]);  
                }else if (line[i] == ' ' || i+1 == line.size()){
                    entradaLeida.push_back(myString(number).toInt());
                    number.clear();
                }
            }
            if (number.size()!=0) {
                entradaLeida.push_back(myString(number).toInt());
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
    for (size_t i = 1; i < registros_.size(); i++) {
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
            //modo inmediato
            if (instruccionActiva->inmediate()) {
    
                acumulador_ = instruccionActiva->apply();

            //esta en modo indirecto
            }else if ( instruccionActiva->indirectMode() ) {

                myString instruct(instruccionActiva->getInstruction());
                myString argument(registros_[instruccionActiva->apply()]);

                if(!instruccionActiva->isCorrect()){
                    std::cerr << "Error de ejecucicón, se ha detenido la máquina" << std::endl;
                    instruccionActiva->show();
                    state_ = false;
                    correct = false;
                    break;
                }

                myString completeInst(instruct.concate(myString(" ")).concate(argument));
                instruction* instruccionDirecta = programa_.createInstruction(completeInst);
                //la nueva instruccion no tiene los punteros
                instruccionDirecta->stablishAcumulador(&acumulador_);
                instruccionDirecta->stablishRegistros(&registros_);

        
                acumulador_ = instruccionDirecta->apply();
                if(!instruccionDirecta->isCorrect()){
                    std::cerr << "Error de ejecucicón, se ha detenido la máquina" << std::endl;
                    instruccionActiva->show();
                    state_ = false;
                    correct = false;
                    delete instruccionDirecta;
                    break;
                }
                delete instruccionDirecta;
            //modo directo
            }else{
                acumulador_ = instruccionActiva->apply();
                if(!instruccionActiva->isCorrect()){
                    std::cerr << "Error de ejecucicón, se ha detenido la máquina" << std::endl;
                    instruccionActiva->show();
                    state_ = false;
                    correct = false;
                    break;
                }
            }
            
            
            if(!instruccionActiva->isCorrect()){
                std::cerr << "Error de ejecucicón, se ha detenido la máquina" << std::endl;
                instruccionActiva->show();
                state_ = false;
                correct = false;
                break;
            }
        }else if (instruccionActiva->kindOf() == myString("jump")) {
            int toJump = instruccionActiva->apply();
            if (toJump != -1) {
                programCounter_ = toJump;
            }else{
                programCounter_++;
            }
        }else if (instruccionActiva->kindOf() == myString("registry")) {
            if (instruccionActiva->indirectMode()) {
                int registro = instruccionActiva->getOperand().cut(1,instruccionActiva->getOperand().size()-1).toInt();
                if (registro <= 0) {
                    std::cerr << "Error se accede a registro inexistente" << std::endl;
                    std::cerr << "Error de ejecucicón, se ha detenido la máquina" << std::endl;
                    instruccionActiva->show();
                    state_ = false;
                    correct = false;
                    break;
                }
                
                int valorReg = registros_[registro]; 
                if (valorReg <= 0) {
                    std::cerr << "Error se accede a registro inexistente" << std::endl;
                    std::cerr << "Error de ejecucicón, se ha detenido la máquina" << std::endl;
                    instruccionActiva->show();
                    state_ = false;
                    correct = false;
                    break;
                }
            }else if (instruccionActiva->inmediate()) {
                
            //modo directo
            }else{
                int registro = instruccionActiva->getOperand().toInt();
                if (registro <= 0) {
                    std::cerr << "Error se accede a registro inexistente" << std::endl;
                    std::cerr << "Error de ejecucicón, se ha detenido la máquina" << std::endl;
                    instruccionActiva->show();
                    state_ = false;
                    correct = false;
                    break;
                }
            }
            
            instruccionActiva->apply();
            if ( !instruccionActiva->isCorrect() ) {
                std::cerr << "Error de ejecucicón, se ha detenido la máquina" << std::endl;
                instruccionActiva->show();
                state_ = false;
                correct = false;
                break;
            }
        }else if (instruccionActiva->kindOf() == myString("memory")) {
            if (instruccionActiva->name() == myString("read")){
                if ( instruccionActiva->indirectMode() ){
                    int pointer = registros_[instruccionActiva->solveIndirection()];
                    std::cout << " " << pointer << std::endl;
                    if (pointer <= 0) {
                        std::cerr << "Error se accede a registro inexistente" << std::endl;
                        std::cerr << "Error de ejecucicón, se ha detenido la máquina" << std::endl;
                        instruccionActiva->show();
                        state_ = false;
                        correct = false;
                        break;
                    }
                    registros_[pointer] = cintaEntrada_.read();
                }else{
                    int reg = instruccionActiva->apply();
                    if (reg <= 0) {
                        std::cerr << "Error se accede a registro inexistente" << std::endl;
                        std::cerr << "Error de ejecucicón, se ha detenido la máquina" << std::endl;
                        instruccionActiva->show();
                        state_ = false;
                        correct = false;
                        break;
                    }
                    registros_[reg] = cintaEntrada_.read();
                }
            }else{
                //es write 
                if (instruccionActiva->inmediate()) {
                    cintaSalida_.write(instruccionActiva->apply());
                }else if (instruccionActiva->indirectMode()) {
                    int reg = instruccionActiva->apply();
                    if (reg <= 0) {
                        std::cerr << "Error se accede a registro inexistente" << std::endl;
                        std::cerr << "Error de ejecucicón, se ha detenido la máquina" << std::endl;
                        instruccionActiva->show();
                        state_ = false;
                        correct = false;
                        break;
                    }
                    int reg2 = registros_[reg];
                    if (reg2 <= 0) {
                        std::cerr << "Error se accede a registro inexistente" << std::endl;
                        std::cerr << "Error de ejecucicón, se ha detenido la máquina" << std::endl;
                        instruccionActiva->show();
                        state_ = false;
                        correct = false;
                        break;
                    }
                    cintaSalida_.write(registros_[reg2]);
                }else{
                    int reg = instruccionActiva->apply();
                    if (reg <= 0) {
                        std::cerr << "Error se accede a registro inexistente" << std::endl;
                        std::cerr << "Error de ejecucicón, se ha detenido la máquina" << std::endl;
                        instruccionActiva->show();
                        state_ = false;
                        correct = false;
                        break;
                    }
                    cintaSalida_.write(registros_[instruccionActiva->apply()]);
                }
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
    }

    if (correct) {
        cintaSalida_.toFile(ficheroSalida_);
        std::cout << "Se han ejecutado: " << instruccionesEjecutadas_  << " instrucciones" << std::endl;
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
            break;
        }
        
        instruction* instruccionActiva = programa_[programCounter_];
        std::cout << "Instruccion que se va a ejecutar: ";
        instruccionActiva->show();
        if (instruccionActiva->kindOf() == myString("math")) {
            //modo inmediato
            if (instruccionActiva->inmediate()) {
                std::cout << "La instruccion es inmediata" << std::endl;
                std::cout << "acumulador = acumulador ";
                if (instruccionActiva->name() == myString("add")) {
                    std::cout << "+";
                }else if(instruccionActiva->name() == myString("sub")){
                    std::cout << "-";
                }else if(instruccionActiva->name() == myString("mult")){
                    std::cout << "*";
                }else if(instruccionActiva->name() == myString("div")){
                    std::cout << "/";
                }
                std::cout << " " << instruccionActiva->getOperand().cut(1,instruccionActiva->getOperand().size()-1).toInt();
                std::cout << std::endl;
    
                acumulador_ = instruccionActiva->apply();

            //esta en modo indirecto
            }else if ( instruccionActiva->indirectMode() ) {
                std::cout << "La instruccion esta en modo indirecto" << std::endl;
                myString instruct(instruccionActiva->getInstruction());
                myString argument(registros_[instruccionActiva->apply()]);

                if(!instruccionActiva->isCorrect()){
                    std::cerr << "Error de ejecucicón, se ha detenido la máquina" << std::endl;
                    instruccionActiva->show();
                    state_ = false;
                    correct = false;
                    break;
                }

                myString completeInst(instruct.concate(myString(" ")).concate(argument));
                instruction* instruccionDirecta = programa_.createInstruction(completeInst);
                //la nueva instruccion no tiene los punteros
                instruccionDirecta->stablishAcumulador(&acumulador_);
                instruccionDirecta->stablishRegistros(&registros_);

                std::cout << "Si resolvemos la indireccion nos queda: ";
                instruccionDirecta->show();

                if ( instruccionDirecta->getOperand().toInt() > 0 ) {
                    std::cout << std::endl << "acumulador = acumulador ";
                    if (instruccionDirecta->name() == myString("add")) {
                        std::cout << "+";
                    }else if(instruccionDirecta->name() == myString("sub")){
                        std::cout << "-";
                    }else if(instruccionDirecta->name() == myString("mult")){
                        std::cout << "*";
                    }else if(instruccionDirecta->name() == myString("div")){
                        std::cout << "/";
                    }
                    std::cout << " " << registros_[instruccionDirecta->getOperand().toInt()];
                    std::cout << std::endl;
                }
                
                acumulador_ = instruccionDirecta->apply();
                if(!instruccionDirecta->isCorrect()){
                    std::cerr << "Error de ejecucicón, se ha detenido la máquina" << std::endl;
                    instruccionActiva->show();
                    state_ = false;
                    correct = false;
                    delete instruccionDirecta;
                    break;
                }
                delete instruccionDirecta;
            //modo directo
            }else{
                std::cout << "La instruccion esta en modo directo" << std::endl;
                instruccionActiva->show();
                acumulador_ = instruccionActiva->apply();
                if(!instruccionActiva->isCorrect()){
                    std::cerr << "Error de ejecucicón, se ha detenido la máquina" << std::endl;
                    instruccionActiva->show();
                    state_ = false;
                    correct = false;
                    break;
                }
                std::cout << "acumulador = acumulador ";
                if (instruccionActiva->name() == myString("add")) {
                    std::cout << "+";
                }else if(instruccionActiva->name() == myString("sub")){
                    std::cout << "-";
                }else if(instruccionActiva->name() == myString("mult")){
                    std::cout << "*";
                }else if(instruccionActiva->name() == myString("div")){
                    std::cout << "/";
                }
                std::cout << " " << registros_[instruccionActiva->getOperand().toInt()];
                std::cout << std::endl;
            }
            
            
            if(!instruccionActiva->isCorrect()){
                std::cerr << "Error de ejecucicón, se ha detenido la máquina" << std::endl;
                instruccionActiva->show();
                state_ = false;
                correct = false;
                break;
            }
        }else if (instruccionActiva->kindOf() == myString("jump")) {
            std::cout << "Instruccion de salto" << std::endl;
            int toJump = instruccionActiva->apply();
            if (toJump != -1) {
                std::cout << "Se cumple la conticion de salto" << std::endl;
                programCounter_ = toJump;
                std::cout << "Se saltara a la instruccion" << programCounter_ << std::endl;
            }else{
                std::cout << "No se cumple la conticion de salto" << std::endl;
                std::cout << "Se continua con el flujo normal de ejecucion" << std::endl;
                programCounter_++;
            }
        }else if (instruccionActiva->kindOf() == myString("registry")) {
            if (instruccionActiva->indirectMode()) {
                std::cout << "Instrucción en modo indirecto" << std::endl;
                int registro = instruccionActiva->getOperand().cut(1,instruccionActiva->getOperand().size()-1).toInt();
                if (registro <= 0) {
                    std::cerr << "Error se accede a registro inexistente" << std::endl;
                    std::cerr << "Error de ejecucicón, se ha detenido la máquina" << std::endl;
                    instruccionActiva->show();
                    state_ = false;
                    correct = false;
                    break;
                }
                
                std::cout << "Tras resolver la indirección se ejecutará:" << std::endl;
                std::cout << instruccionActiva->getInstruction().string() << " ";
                int valorReg = registros_[registro];
                std::cout << valorReg << std::endl; 
                if (valorReg <= 0) {
                    std::cerr << "Error se accede a registro inexistente" << std::endl;
                    std::cerr << "Error de ejecucicón, se ha detenido la máquina" << std::endl;
                    instruccionActiva->show();
                    state_ = false;
                    correct = false;
                    break;
                }
            }else if (instruccionActiva->inmediate()) {
                std::cout << "Instrucción en modo inmediato" << std::endl;
                std::cout << "Se carga en el acumulador un ";
                std::cout << instruccionActiva->getOperand().cut(1,instruccionActiva->getOperand().size()-1).string();
                std::cout << std::endl;
            //modo directo
            }else{
                std::cout << "Instrucción en modo directo" << std::endl;
                int registro = instruccionActiva->getOperand().toInt();
                if (registro <= 0) {
                    std::cerr << "Error se accede a registro inexistente" << std::endl;
                    std::cerr << "Error de ejecucicón, se ha detenido la máquina" << std::endl;
                    instruccionActiva->show();
                    state_ = false;
                    correct = false;
                    break;
                }
                std::cout << "Se carga en el registro ";
                std::cout << registro << " un ";
                std::cout << acumulador_ << std::endl;
            }
            
            instruccionActiva->apply();
            if ( !instruccionActiva->isCorrect() ) {
                std::cerr << "Error de ejecucicón, se ha detenido la máquina" << std::endl;
                instruccionActiva->show();
                state_ = false;
                correct = false;
                break;
            }
        }else if (instruccionActiva->kindOf() == myString("memory")) {
            if (instruccionActiva->name() == myString("read")){
                if ( instruccionActiva->indirectMode() ){
                    std::cout << "Instruccion en modo indirecto" << std::endl;
                    std::cout << "Tras resolver la indireccion se ejecutara:" << std::endl;
                    std::cout << instruccionActiva->getInstruction().string();
                    int pointer = registros_[instruccionActiva->solveIndirection()];
                    std::cout << " " << pointer << std::endl;
                    if (pointer <= 0) {
                        std::cerr << "Error se accede a registro inexistente" << std::endl;
                        std::cerr << "Error de ejecucicón, se ha detenido la máquina" << std::endl;
                        instruccionActiva->show();
                        state_ = false;
                        correct = false;
                        break;
                    }
                    registros_[pointer] = cintaEntrada_.read(); 
                    std::cout << "Se carga un " << registros_[pointer] << " en registro " << pointer << std::endl;
                }else{
                    int reg = instruccionActiva->apply();
                    if (reg <= 0) {
                        std::cerr << "Error se accede a registro inexistente" << std::endl;
                        std::cerr << "Error de ejecucicón, se ha detenido la máquina" << std::endl;
                        instruccionActiva->show();
                        state_ = false;
                        correct = false;
                        break;
                    }
                    registros_[reg] = cintaEntrada_.read();
                    std::cout << "Instruccion en modo directo" << std::endl;
                    std::cout << "Se carga " << registros_[reg] << " en registro " << reg << std::endl;
                }
            }else{
                //es write 
                if (instruccionActiva->inmediate()) {
                    std::cout << "Instruccion en modo inmediato" << std::endl;
                    std::cout << "Se escribira " << instruccionActiva->apply();
                    std::cout << " en la cinta de salida" << std::endl;
                    cintaSalida_.write(instruccionActiva->apply());
                }else if (instruccionActiva->indirectMode()) {
                    std::cout << "Instruccion en modo indirecto" << std::endl;
                    int reg = instruccionActiva->apply();
                    if (reg <= 0) {
                        std::cerr << "Error se accede a registro inexistente" << std::endl;
                        std::cerr << "Error de ejecucicón, se ha detenido la máquina" << std::endl;
                        instruccionActiva->show();
                        state_ = false;
                        correct = false;
                        break;
                    }
                    std::cout << "Tras resolver la indireccion se ejecutara" << std::endl;
                    std::cout << instruccionActiva->getInstruction().string();
                    int reg2 = registros_[reg];
                    std::cout << " " << reg2 << std::endl;
                    if (reg2 <= 0) {
                        std::cerr << "Error se accede a registro inexistente" << std::endl;
                        std::cerr << "Error de ejecucicón, se ha detenido la máquina" << std::endl;
                        instruccionActiva->show();
                        state_ = false;
                        correct = false;
                        break;
                    }
                    cintaSalida_.write(registros_[reg2]);
                }else{
                    std::cout << "Instruccion en modo directo" << std::endl;
                    int reg = instruccionActiva->apply();
                    if (reg <= 0) {
                        std::cerr << "Error se accede a registro inexistente" << std::endl;
                        std::cerr << "Error de ejecucicón, se ha detenido la máquina" << std::endl;
                        instruccionActiva->show();
                        state_ = false;
                        correct = false;
                        break;
                    }
                    std::cout << "Se escribira el contenido del registro ";
                    std::cout << reg << std::endl;
                    std::cout << "Se escribira " << registros_[reg];
                    std::cout << " en la cinta de salida" << std::endl;
                    cintaSalida_.write(registros_[instruccionActiva->apply()]);
                }
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
        if (correct) {
            std::cout << std::endl;
            showState();
            std::cout << std::endl << std::endl;
            std::cout << "Para continuar, introduzca cualquier caracter y pulse enter" << std::endl;
            char a;
            std::cin >> a;
        }
        
    }

    if (correct) {
        std::cout << "Todo salio correctamente, exportando en " << ficheroSalida_ << std::endl;
        cintaSalida_.toFile(ficheroSalida_);
        std::cout << "Se han ejecutado: " << instruccionesEjecutadas_  << " instrucciones" << std::endl;
    }
}
