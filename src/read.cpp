#include "../include/read.hpp"

int read::solveIndirection(void){
    // eliminamos el * y cargamos el valor del registro
    //int position = instruction::operand_.cut(1,instruction::operand_.size()-1).toInt();
    // devolvemos el valor del registro apuntado
    //return memoryInstruction::registros_->operator[](position);
    //return position;
    return instruction::operand_.cut(1,instruction::operand_.size()-1).toInt();
}

//guarda lo que haya en la cinta de entrada en el reg que le digas 
int read::apply(void){
    /*int registerToReturn;
    //esta en modo indirecto
    if (instruction::operand_.contains(myString("*"))){
        registerToReturn = memoryInstruction::registros_->operator[](solveIndirection()); 
    //esta en modo normal
    }else{
    std::cout << "here" << std::endl;
        registerToReturn = memoryInstruction::registros_->operator[](instruction::operand_.toInt()); 
    }
    registerToReturn = instruction::operand_.toInt(); 
    return registerToReturn;*/
    return instruction::operand_.toInt();
}

/*
y si hago que devuelva el indice al que tiene que buscar luego la maquina? 
la maquina haria algo en plan reg[instruction.apply] = cintaEntrada.read()
con un flag que indica si tiene indireccion activa, indirectMode()
 si tiene indireccion haria
reg[instruction.solveIndirection()] = cintaEntrada.read()
reg[reg[instruction.apply()]] = cintaEntrada.read()
*/
