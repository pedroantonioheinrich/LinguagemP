#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gerador.h"
#include "lexico.h"

static FILE* saida;

void gerador_abrir(const char* nome_arquivo) {
    saida = fopen(nome_arquivo, "w");
    if (!saida) {
        perror("Erro ao abrir arquivo de saída");
        exit(1);
    }
}

void gerador_fechar() {
    if (saida) {
        fclose(saida);
        saida = NULL;
    }
}

void gerador_escrever(const char* texto) {
    if (saida) {
        fprintf(saida, "%s", texto);
    }
}

// Esta função auxilia na tradução direta de expressões simples
void gerador_traduzir_token(Token t) {
    if (!saida) return;

    switch (t.tipo) {
        case TOKEN_IDENTIFICADOR:
        case TOKEN_INTEIRO:
        case TOKEN_REAL:
            gerador_escrever(t.lexema);
            break;
        case TOKEN_CADEIA:
            gerador_escrever("\"");
            gerador_escrever(t.lexema);
            gerador_escrever("\"");
            break;
        case TOKEN_ATRIBUICAO:
            gerador_escrever(" = ");
            break;
        case TOKEN_IGUAL:
            gerador_escrever(" == ");
            break;
        case TOKEN_OPERADOR:
            gerador_escrever(t.lexema);
            break;
        default:
            // Outros tokens são tratados diretamente pelo sintático
            break;
    }
}