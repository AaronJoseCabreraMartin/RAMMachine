#include "../include/RAMMachine.hpp"

int main(){

    std::cout << "test7.ram" << std::endl;
    RAMMachine myRAMMachine7("input.txt","output.txt","ejemplosRAM/test7.ram",true);
    myRAMMachine7.showState();
    std::cout << std::endl << std::endl;


    return 0;
}