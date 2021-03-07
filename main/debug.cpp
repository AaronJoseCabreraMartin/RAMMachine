#include "../include/RAMMachine.hpp"

#include <iostream>

int main(void) {
    myString prueba(123456789);
    myString prueba2("+1");

    std::cout << prueba.concate(prueba2).string() << std::endl;
    
    return 0;
}