# Nome do módulo
MODULE_NAME = simple

# Nome do zip
ZIP_NAME = $(MODULE_NAME)

# Lista de arquivos fonte
SOURCES = $(MODULE_NAME).c

# Lista todos os arquivos envolvidos
FILES = $(SOURCES) $(HEADERS) Makefile

# Diretório do kernel
KDIR = /lib/modules/$(shell uname -r)/build

# Adiciona o arquivo .o ao obj-m para indicar que ele é um módulo
obj-m += $(MODULE_NAME).o

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

# finish: Compila, carrega, remove e zippa
finish: all run unload clean zip

.PHONY: all clean run zip unload finish
