#include "../include/RAMMachine.hpp"

#include <iostream>

int main(void) {
    myString prueba("0123456789");

    std::cout << prueba.string() << std::endl;
    std::cout << prueba.cut(3,5).string() << std::endl;
    std::cout << prueba.cut(7).string() << std::endl;
    if (prueba.contains(myString("56"))) {
        std::cout << "contiene" << std::endl;
    }else{
        std::cout << "no contiene" << std::endl;
    }
    
    return 0;
}