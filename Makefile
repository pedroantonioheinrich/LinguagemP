# Configurações do Compilador
CC = gcc
CFLAGS = -Wall -Wextra -g -DDEBUG
TARGET = lp_compilador

# Caminhos e Arquivos
SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:.c=.o)

# Cores para o terminal
BLUE = \033[1;34m
RESET = \033[0m

.PHONY: all audit run clean

# Regra principal
all: $(TARGET)

$(TARGET): $(OBJ)
	@echo "$(BLUE)--- Vinculando Objetos ---$(RESET)"
	$(CC) $(CFLAGS) $^ -o $@

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "$(BLUE)--- Compilando $< ---$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

FONTE_TESTE = exemplos/teste_vetores1.lp 

# Auditoria: agora depende explicitamente do clean e do target
audit: clean $(TARGET)
	@echo "$(BLUE)--- Iniciando Auditoria de Compilacao ---$(RESET)"
	./$(TARGET) $(FONTE_TESTE) > auditoria_saida.log 2>&1 || (cat auditoria_saida.log && exit 1)
	@echo "$(BLUE)--- Log de Auditoria ---$(RESET)"
	@cat auditoria_saida.log
	@echo "\n$(BLUE)--- Codigo Gerado ---$(RESET)"
	@if [ -f codigo_gerado.c ]; then cat codigo_gerado.c; else echo "Arquivo codigo_gerado.c não encontrado"; fi

# Regra RUN: Adicionei 'clean' antes de 'audit' para garantir a limpeza total
run: clean audit
	@echo "$(BLUE)--- Tentando Compilar Codigo Gerado ---$(RESET)"
	@if [ -f codigo_gerado.c ]; then \
		gcc codigo_gerado.c -o meu_programa_p && \
		echo "$(BLUE)--- Executando Programa Final ---$(RESET)" && \
		./meu_programa_p; \
	else \
		echo "Erro: codigo_gerado.c não existe. Verifique o log de auditoria."; \
	fi

# Limpeza profunda
clean:
	@echo "$(BLUE)--- Limpando Arquivos Temporários ---$(RESET)"
	rm -f $(SRC_DIR)/*.o $(TARGET) codigo_gerado.c programa_final.c meu_programa_p auditoria_saida.log codigo_generated.c utils.lp.c