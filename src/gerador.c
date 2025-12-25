#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gerador.h"
#include "lexico.h"

static FILE* saida_c;

void gerador_abrir(const char* nome_arquivo) {
    saida_c = fopen(nome_arquivo, "w");
    if (!saida_c) {
        perror("Erro ao abrir arquivo de saida");
        exit(1);
    }
    // Inclui bibliotecas padrão necessárias para o hardware simulado e IO
    fprintf(saida_c, "#include <stdio.h>\n");
    fprintf(saida_c, "#include <unistd.h>\n");
    fprintf(saida_c, "#include <stdbool.h>\n\n");
}

void gerador_fechar() {
    if (saida_c) {
        fclose(saida_c);
    }
}

void gerador_escrever(const char* texto) {
    if (saida_c) {
        fprintf(saida_c, "%s", texto);
    }
}

void gerador_traduzir_token(Token t) {
    if (!saida_c) return;

    switch (t.tipo) {
        case TOKEN_INICIO:
            // O sintatico agora cuida de escrever 'int main()', 
            // mas deixamos aqui caso precise de um placeholder
            break;

        case TOKEN_VALOR:
        case TOKEN_IDENTIFICADOR:
        case TOKEN_OPERADOR:
            // Para operadores (+, -, %, <, ==) e valores, 
            // escrevemos o lexema diretamente com espaços
            fprintf(saida_c, " %s ", t.lexema);
            break;

        case TOKEN_CADEIA:
            fprintf(saida_c, "\"%s\"", t.lexema);
            break;

        case TOKEN_ATRIBUICAO:
            fprintf(saida_c, " = ");
            break;

        case TOKEN_PONTO_VIRGULA:
            fprintf(saida_c, ";\n");
            break;

        default:
            // Outros tokens são ignorados ou tratados pelo sintatico
            break;
    }
}