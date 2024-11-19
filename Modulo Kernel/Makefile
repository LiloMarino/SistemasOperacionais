# Nome do módulo
MODULE_NAME = simple

# Nome do zip
ZIP_NAME = $(MODULE_NAME)

# Lista de arquivos fonte
SOURCES = $(MODULE_NAME).c

# Lista de headers (se houver)
HEADERS = 

# Lista todos os arquivos envolvidos
FILES = $(SOURCES) $(HEADERS) Makefile

# Definir o compilador
CXX = gcc

# Flags para a compilação do módulo
CXXFLAGS = -Wall -Wextra

# Diretório do kernel
KDIR = /lib/modules/$(shell uname -r)/build

# Alvo padrão
all: $(MODULE_NAME).ko

# Regras de compilação
$(MODULE_NAME).ko: $(SOURCES)
	make -C $(KDIR) M=$(PWD) modules

# run: Carregar o módulo e verificar o log
run: $(MODULE_NAME).ko
	sudo insmod $(MODULE_NAME).ko
	dmesg | tail

# clean: Limpa os arquivos gerados pela compilação
clean:
	make -C $(KDIR) M=$(PWD) clean
	rm -f *.zip

# zip: Zippa os arquivos fonte e outros necessários
zip: $(ZIP_NAME).zip

$(ZIP_NAME).zip: $(FILES)
	zip -r $(ZIP_NAME).zip $(FILES)
	unzip -q $(ZIP_NAME).zip -d $(ZIP_NAME)

# unload: Remove o módulo do kernel
unload:
	sudo rmmod $(MODULE_NAME)
	dmesg | tail

finish: all run unload clean zip

.PHONY: all clean run zip unload finish
