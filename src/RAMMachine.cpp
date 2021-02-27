#include "../include/RAMMachine.hpp"

RAMMachine::RAMMachine(const std::string& entrada, const std::string& salida,
                        const std::string& programa, const bool& modo): programa_(programa){
    ficheroSalida_ = salida;
    debug_ = modo;//true debug false normal
    programCounter_ = 0;
    acumulador_ = 0;
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
    }else{
        std::cerr << "Error, fichero " << entrada << " no se ha podido leer" << std::endl;
    }
}


void RAMMachine::showState(void)const{
    std::cout << "Estado actual: " << (state_ ? "Activo" : "HALT") << std::endl;
    std::cout << "Modo Debug: " << (debug_ ? "Activado" : "Desactivado") << std::endl;
    std::cout << "Cinta Entrada: ";
    cintaEntrada_.show();
    std::cout << std::endl << "Cinta Salida: ";
    cintaSalida_.show();
    std::cout << std::endl;
    std::cout << "Estado actual de los registros:" << std::endl;
    for (size_t i = 0; i < registros_.size(); i++) {
        std::cout << " R[" << i << "] = " << registros_[i] << std::endl;
    }
    std::cout << "Acumulador: " << acumulador_ << std::endl;
    std::cout << "Contador de Programa: " << programCounter_ << std::endl;
    std::cout << "Programa Cargado: " << std::endl;
    programa_.showProgram();
}