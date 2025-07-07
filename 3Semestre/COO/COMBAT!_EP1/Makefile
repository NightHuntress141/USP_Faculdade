# Makefile para o projeto Combat!

# Diretório do projeto
SRC_DIR = src

# Classe principal
MAIN_CLASS = Combat

# Buscar todos os arquivos .java no diretório src
SOURCES := $(shell find $(SRC_DIR) -name '*.java')

# Compilar todos os arquivos .java no próprio diretório src
compile:
	@javac $(SOURCES)
	@echo "Compilação concluída."

# Executar o programa
run: compile
	@java -cp $(SRC_DIR) $(MAIN_CLASS)

# Remover arquivos compilados (.class) gerados a partir dos .java
# (não remove os .class que já vieram prontos!)
clean:
	@find $(SRC_DIR) -name '*.class' -delete
	@echo "Arquivos .class removidos."

.PHONY: compile run clean
