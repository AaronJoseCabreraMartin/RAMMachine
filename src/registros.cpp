#include "../include/registros.hpp"


registros::registros(const std::vector<int>& inicial){
    set(inicial);
}


int& registros::operator[](const int& index){
    if (index < registros_.size()) {
        return registros_[index];
    }
    while (index <= registros_.size()) {
        registros_.insert_tail(0);
    }
    return registros_[index];
}

int registros::operator[](const int& index)const{
    if (index < registros_.size()) {
        return registros_[index];
    }else{
        std::cerr << "Registro no disponible, se esta accediendo con const..." << std::endl;
        return 0;
    }
}


void registros::show(void)const{
    for (size_t i = 0; i < registros_.size(); i++) {
        std::cout << registros_[i] << " ";
    }
}


void registros::set(const std::vector<int>& nuevoEstado){
    registros_.clear();
    for (size_t i = 0; i < nuevoEstado.size(); i++) {
        registros_.insert_tail(nuevoEstado[i]);
    }
}

