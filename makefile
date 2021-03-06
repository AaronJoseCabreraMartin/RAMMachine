all: main/main.cpp
	g++ -O3 main/main.cpp src/RAMMachine.cpp src/cinta.cpp src/cintaSalida.cpp src/cintaEntrada.cpp src/myString.cpp src/program.cpp src/instruction.cpp src/registros.cpp -o bin/ram_sim

debug: main/debug.cpp
	g++ -g main/debug.cpp src/RAMMachine.cpp src/cinta.cpp src/cintaSalida.cpp src/cintaEntrada.cpp src/myString.cpp src/program.cpp src/instruction.cpp src/registros.cpp -o bin/ram_sim

clean:
	rm bin/ram_sim