# Nome do executável
EXEC_NAME = tarefa1

# Nome do zip
ZIP_NAME = MuriloAldigueriMarino

# Lista de arquivos fonte
SOURCES = tarefa1.c

# Lista de headers (se houver)
# HEADERS = $(patsubst %.cpp,%.hpp,$(filter-out main.cpp,$(SOURCES)))
HEADERS = checkPassword.h

# Lista todos os arquivos envolvidos
FILES = $(SOURCES) $(HEADERS) Makefile

# Definir o compilador
CXX = gcc

# Definir flags do compilador
CXXFLAGS = -Wall -Wextra

# Gerar a lista de arquivos objeto a partir dos arquivos fonte
OBJECTS = $(SOURCES:.c=.o) checkPassword.o

# Alvo padrão
all: $(EXEC_NAME)

# Regras de compilação
$(EXEC_NAME): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

-include $(OBJECTS:.o=.d)

# run: Compila e roda o programa
run: all $(EXEC_NAME)
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
