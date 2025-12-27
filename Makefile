# ==========================================
# MAKEFILE - COMPILADOR LINGUAGEM P
# ==========================================

TARGET = compilador_p
CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude

SRC_DIR = src
OBJ_DIR = obj
TEST_DIR = tests
GEN_DIR = $(TEST_DIR)/gerados

# Lista de fontes completa
SRCS = $(SRC_DIR)/principal.c \
       $(SRC_DIR)/lexico.c \
       $(SRC_DIR)/logs.c \
       $(SRC_DIR)/sintatico.c \
       $(SRC_DIR)/semantico.c \
       $(SRC_DIR)/gerador.c \
       $(SRC_DIR)/formatador_c.c \
       $(SRC_DIR)/tradutor_string.c \
       $(SRC_DIR)/tradutor_expressao.c \
       $(SRC_DIR)/tradutor_variavel.c \
       $(SRC_DIR)/tradutor_fluxo.c \
       $(SRC_DIR)/tradutor_registro.c \
       $(SRC_DIR)/tradutor_funcao.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	@echo "------------------------------------------------"
	@echo "Executável '$(TARGET)' gerado com sucesso."
	@echo "------------------------------------------------"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# --- LOOP DE TESTES COM ORGANIZAÇÃO DE ARQUIVOS .C ---
test_all: $(TARGET)
	@mkdir -p $(GEN_DIR)
	@echo "Iniciando bateria de testes em $(TEST_DIR)/..."
	@for file in $(shell ls $(TEST_DIR)/*.lp 2>/dev/null); do \
		base_name=$$(basename $$file .lp); \
		./$(TARGET) $$file > /dev/null 2>&1; \
		if [ $$? -eq 0 ]; then \
			echo "Testando $$file... ✅ OK"; \
			if [ -f codigo_gerado.c ]; then \
				mv codigo_gerado.c $(GEN_DIR)/$$base_name.c; \
			fi \
		else \
			echo "Testando $$file... ❌ ERRO ENCONTRADO!"; \
			echo "------------------------------------------------"; \
			echo "CONTEÚDO DO ARQUIVO: $$file"; \
			echo "------------------------------------------------"; \
			cat $$file; \
			echo ""; \
			echo "------------------------------------------------"; \
		fi \
	done

clean:
	rm -rf $(OBJ_DIR) $(TARGET) codigo_gerado.c *.log
	rm -rf $(GEN_DIR)
	@echo "Limpeza concluída. Pasta $(GEN_DIR) removida."

.PHONY: clean test_all