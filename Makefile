# Nome do executável
EXEC_NAME = program

# Argumentos para o executável
ARGUMENTS = addresses.txt 256 FIFO

# Nome do zip
ZIP_NAME = MuriloMarino_MemoriaVirtual

# Diretórios
SRC_DIR = src
BUILD_DIR = build

# Arquivos do projeto principal
SRC_SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
SRC_OBJECTS = $(SRC_SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Definir o compilador
CXX = g++

# Definir flags do compilador
CXXFLAGS = -Wall -Wextra -std=c++17 -g

# Alvo padrão
all: $(EXEC_NAME)

# Regra de compilação do executável
$(EXEC_NAME): $(SRC_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regras para compilar arquivos .cpp em .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Alvo para limpar os arquivos gerados
clean:
	rm -rf $(BUILD_DIR) $(EXEC_NAME)

# Alvo para executar o programa
run: all $(EXEC_NAME)
	./$(EXEC_NAME) $(ARGUMENTS)

# Alvo para criar um zip com os arquivos fonte
zip:
	zip -r $(ZIP_NAME).zip $(SRC_DIR) Makefile
	mkdir -p $(ZIP_NAME)
	unzip -q $(ZIP_NAME).zip -d $(ZIP_NAME)

# Regra para executar o programa com o Valgrind
valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXEC_NAME)

.PHONY: all clean run zip
