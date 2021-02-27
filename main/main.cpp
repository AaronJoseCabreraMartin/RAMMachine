#include "../include/RAMMachine.hpp"

int main(){
    RAMMachine myRAMMachine("input.txt","output.txt","ejemplosRAM/test4.ram",true);
    myRAMMachine.showState();

    return 0;
}