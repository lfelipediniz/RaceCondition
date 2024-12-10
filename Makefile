# compilador
CXX := g++

# diretórios
SRC_DIR := src
BUILD_DIR := build
INCLUDE_DIR := include

# flags de compilação
CXXFLAGS := -Wall -Wextra -std=c++17 -I$(INCLUDE_DIR)

# arquivos fonte e objetos
SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SOURCES))

# nome do executável
TARGET := $(BUILD_DIR)/jogo

# regra padrão
all: $(TARGET)

# regra para criar o executável
$(TARGET): $(OBJECTS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# regra para compilar os arquivos objeto
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# limpa arquivos compilados
clean:
	rm -rf $(BUILD_DIR)/*

# limpa tudo, incluindo o diretório build
cleanall:
	rm -rf $(BUILD_DIR)

# regra para rodar o programa
run: $(TARGET)
	$(TARGET)

# phony targets
.PHONY: all clean cleanall run
