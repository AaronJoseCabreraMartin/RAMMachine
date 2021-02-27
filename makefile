all: main/main.cpp
	g++ -O3 main/main.cpp src/RAMMachine.cpp src/cinta.cpp src/cintaSalida.cpp src/cintaEntrada.cpp src/myString.cpp src/program.cpp src/instruction.cpp -o bin/RAMMachine

debug: main/main.cpp
	g++ -g main/main.cpp src/RAMMachine.cpp src/cinta.cpp src/cintaSalida.cpp src/cintaEntrada.cpp src/myString.cpp src/program.cpp src/instruction.cpp -o bin/RAMMachine

clean:
	rm bin/RAMMachine