#include "../include/RAMMachine.hpp"

void ayuda(void){
    std::cout << "ram_sim recibe al menos 4 parámetros, puede recibir un quinto opcionalmente" << std::endl;
    std::cout << "Los parámetros que puede recibir se encuentran detallados en la siguiente lista:" << std::endl;
    std::cout << " 1- Programa formato RAM. Almacenado en un fichero con extensión \".ram\"" << std::endl;
    std::cout << " 2- Contenido de la cinta de entrada. Almacenado en un";
    std::cout << " fichero con extensión \".in\"" << std::endl;
    std::cout << " 3- Fichero en el que se volcará el contenido de la cinta de salida.";
    std::cout << " Se almacenará en un fichero con extensión \".out\"" << std::endl;
    std::cout << " 4- [Opcional] Activar el modo depuración. (Con un 1)" << std::endl;
    std::cout << std::endl << "Ejemplo de ejecución:" << std::endl;
    std::cout << " ./bin/ram_sim ejemplosRAM/test1.ram entrada.in salida.out 1" << std::endl;
}

int main(int argc, char *argv[]){
    //./ram_sim ram_program.ram input_tape.in output_tape.out debug
    if (argc < 4){
        std::cout << "Número de parámetros insuficiente" << std::endl;
        ayuda();
        return 1;
    }
    bool debug = false;
    if (argc == 5) {
        debug = myString(argv[4]) == myString("1");
    }
    RAMMachine myRAMMachine(argv[2],argv[3],argv[1],debug);
    if (debug){
        bool salir = false;
        int sys;
        char opcion;
        //sys = system("clear");
        while (!salir) {
            std::cout << std::endl;
            std::cout << ">h" << std::endl;
            std::cout << "r: ver los registros" << std::endl;
            std::cout << "t: traza" << std::endl;
            std::cout << "e: ejecutar" << std::endl;
            std::cout << "s: desensamblador" << std::endl;
            std::cout << "i: ver cinta entrada" << std::endl;
            std::cout << "o: ver cinta salida" << std::endl;
            std::cout << "h: ayuda" << std::endl;
            std::cout << "x: salir" << std::endl;
            std::cout << ">" << std::endl;
            std::cin >> opcion;
            //sys = system("clear");
            switch (opcion) {
                case 'r':
                    myRAMMachine.showRegisters();
                    break;
                case 't':
                    std::cout << "Ejecutaría pero en modo traza" << std::endl;
                    salir = true;
                    break;
                case 'e':
                    myRAMMachine.execute();
                    salir = true;
                    break;
                case 's':
                    myRAMMachine.showPrograma();
                    break;
                case 'i':
                    myRAMMachine.showCintaEntrada();
                    break;
                case 'o':
                    myRAMMachine.showCintaSalida();
                    break;
                case 'h':
                    ayuda();
                    break;
                case 'x':
                    salir = true;
                    break;
                default:
                    std::cout << "Opción " << opcion << " no existe" << std::endl;
                    std::cout << "Pruebe con alguna de las opciones del menú" << std::endl;
                    break;
            }
        }
    }else{
        myRAMMachine.execute();
    }
    
    


    return 0;
}