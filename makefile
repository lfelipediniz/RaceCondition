# Nome do executável
EXEC = jogo

# Compilador
CXX = g++

# Flags de compilação
CXXFLAGS = -Wall -std=c++20

# Objetos
OBJ = carro.o jogo.o

# Regra principal
$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJ)

# Compilar carro.o
carro.o: carro.cpp carro.h
	$(CXX) $(CXXFLAGS) -c carro.cpp

# Compilar jogo.o
jogo.o: jogo.cpp jogo.h
	$(CXX) $(CXXFLAGS) -c jogo.cpp

# Limpeza
clean:
	rm -f $(OBJ) $(EXEC)
