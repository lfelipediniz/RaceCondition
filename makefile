# Definindo o compilador e as flags
CXX = g++
CXXFLAGS = -std=c++11 -pthread

# Diretórios de origem e de objetos
SRCDIR = .
OBJDIR = obj

# Arquivos fonte
SOURCES = $(SRCDIR)/Carro.cpp $(SRCDIR)/Jogo.cpp $(SRCDIR)/main.cpp

# Arquivos objeto
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Nome do executável
EXEC = jogo

# Regra para compilar o executável
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regra para compilar arquivos .cpp em arquivos .o
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)  # Cria o diretório de objetos, se não existir
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para limpar os arquivos gerados
clean:
	rm -rf $(OBJDIR) $(EXEC)

# Regra para executar o programa
run: $(EXEC)
	./$(EXEC)
