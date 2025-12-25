# Nome do compilador
CC = gcc

# Flags de compilação (Avisos, Debug e Includes)
CFLAGS = -Wall -Wextra -g

# Nome do executável final do compilador
TARGET = lp_compilador

# Lista de arquivos objeto (todos os .c que criamos)
OBJS = src/logs.o \
       src/lexico.o \
       src/gerador.o \
       src/semantico.o \
       src/sintatico.o \
       src/principal.o

# Regra principal: compilar o projeto
all: $(TARGET)

# Como gerar o executável a partir dos objetos
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Regra para compilar cada arquivo .c em um .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra especial para rodar o teste atual (teste_logica.lp)
run: all
	./$(TARGET) exemplos/teste_v16.lp
	gcc codigo_gerado.c -o meu_programa_p
	./meu_programa_p

# Limpar arquivos temporários e binários
clean:
	rm -f src/*.o $(TARGET) codigo_gerado.c meu_programa_p

# Ajuda para o usuário
help:
	@echo "Comandos disponíveis:"
	@echo "  make        - Compila o compilador da Linguagem P"
	@echo "  make run    - Compila e executa o teste exemplos/teste_logica.lp"
	@echo "  make clean  - Remove arquivos compilados e temporários"