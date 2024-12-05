# Nome do executável
EXEC_NAME = barbeiro

# Nome do zip
ZIP_NAME = MuriloAldigueriMarino

# Lista de arquivos fonte
SOURCES = main.cpp

# Lista de headers (se houver)
HEADERS = $(patsubst %.cpp,%.hpp,$(filter-out main.cpp,$(SOURCES)))

# Lista todos os arquivos envolvidos
FILES = $(SOURCES) $(HEADERS) Makefile

# Definir o compilador
CXX = g++

# Definir flags do compilador
CXXFLAGS = -Wall -Wextra -pthread -std=c++17

# Gerar a lista de arquivos objeto a partir dos arquivos fonte
OBJECTS = $(SOURCES:.cpp=.o)

# Alvo padrão
all: $(EXEC_NAME)

# Regras de compilação
$(EXEC_NAME): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Incluir arquivos .d para dependências
-include $(OBJECTS:.o=.d)

# run: Compila e roda o programa
run: all
	./$(EXEC_NAME)

# zip: Zippa os arquivos fonte e relatório
zip: $(ZIP_NAME).zip

$(ZIP_NAME).zip: $(FILES)
	zip -r $(ZIP_NAME).zip $(FILES)
	unzip -q $(ZIP_NAME).zip -d $(ZIP_NAME)

# clean: Limpa todos os arquivos gerados da compilação
clean:
	rm -f $(EXEC_NAME)
	rm -f *.o
	rm -f *.d

# valgrind: Regra para executar o programa com o Valgrind
valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXEC_NAME)

finish: all run clean zip

.PHONY: all clean run zip valgrind finish
