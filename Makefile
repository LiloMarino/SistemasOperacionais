# Nome do executável
EXEC_NAME = programa

# Nome do zip
ZIP_NAME = programa

# Lista de arquivos fonte
SOURCES = main.cpp

# Lista de headers automaticamente (qualquer .cpp que não seja main.cpp)
HEADERS = $(patsubst %.cpp,%.hpp,$(filter-out main.cpp,$(SOURCES)))

# Lista todos os arquivos envolvidos
FILES = $(SOURCES) $(HEADERS) Makefile

# Definir o compilador
CXX = g++

# Definir flags do compilador
CXXFLAGS = -Wall -Wextra -std=c++17 -g

# Gerar a lista de arquivos objeto a partir dos arquivos fonte
OBJECTS = $(SOURCES:.cpp=.o)

# Alvo padrão
all: $(LEXER) $(PARSER) $(EXEC_NAME)

# Regras de compilação
$(EXEC_NAME): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

-include $(OBJECTS:.o=.d)

# run: Compila e roda o programa
run: all $(EXEC_NAME)
	./$(EXEC_NAME)

# zip: Zippa os arquivos fonte
zip: $(ZIP_NAME).zip

$(ZIP_NAME).zip: $(FILES)
	zip -r $(ZIP_NAME).zip $(FILES)
	mkdir -p $(ZIP_NAME)
	unzip -q $(ZIP_NAME).zip -d $(ZIP_NAME)

# clean: Limpa todos os arquivos gerados da compilação
clean:
	rm -f $(OBJECTS)
	rm -f $(SOURCES:.cpp=.d)
	rm -f $(EXEC_NAME)
	rm -f *.o

# valgrind: Regra para executar o programa com o Valgrind
valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXEC_NAME)

finish: all run clean zip

.PHONY: all clean run zip
