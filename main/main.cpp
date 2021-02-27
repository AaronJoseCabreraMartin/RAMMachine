#include "../include/RAMMachine.hpp"

int main(){
    RAMMachine myRAMMachine("input.txt","output.txt","test1.ram",true);
    myRAMMachine.showState();
    return 0;
}