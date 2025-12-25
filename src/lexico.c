#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "lexico.h"

int linha_atual = 1;
int coluna_atual = 1;

Token criar_token(TipoToken tipo, const char* lexema) {
    Token t;
    t.tipo = tipo;
    strncpy(t.lexema, lexema, 99);
    t.lexema[99] = '\0';
    t.linha = linha_atual;
    t.coluna = coluna_atual;
    return t;
}

Token proximo_token(FILE *arquivo) {
    int c;
    while ((c = fgetc(arquivo)) != EOF) {
        coluna_atual++;
        if (c == '\n') { linha_atual++; coluna_atual = 1; continue; }
        if (isspace(c)) continue;

        if (c == '/') {
            int prox = fgetc(arquivo);
            if (prox == '/') {
                while ((c = fgetc(arquivo)) != '\n' && c != EOF);
                linha_atual++; coluna_atual = 1;
                continue;
            } else { ungetc(prox, arquivo); }
        }

        if (c == '%') return criar_token(TOKEN_OPERADOR, "%");
        if (c == '(') return criar_token(TOKEN_ABRE_PARENTESES, "(");
        if (c == ')') return criar_token(TOKEN_FECHA_PARENTESES, ")");
        if (c == '{') return criar_token(TOKEN_ABRE_CHAVE, "{");
        if (c == '}') return criar_token(TOKEN_FECHA_CHAVE, "}");
        if (c == ';') return criar_token(TOKEN_PONTO_VIRGULA, ";");
        if (c == ',') return criar_token(TOKEN_VIRGULA, ",");
        
        // Lógica para =, ==
        if (c == '=') {
            int prox = fgetc(arquivo);
            if (prox == '=') return criar_token(TOKEN_OPERADOR, "==");
            ungetc(prox, arquivo);
            return criar_token(TOKEN_ATRIBUICAO, "=");
        }

        // Lógica para +, +=
        if (c == '+') {
            int prox = fgetc(arquivo);
            if (prox == '=') return criar_token(TOKEN_MAIS_IGUAL, "+=");
            ungetc(prox, arquivo);
            return criar_token(TOKEN_OPERADOR, "+");
        }

        // Lógica para -, -=
        if (c == '-') {
            int prox = fgetc(arquivo);
            if (prox == '=') return criar_token(TOKEN_MENOS_IGUAL, "-=");
            ungetc(prox, arquivo);
            return criar_token(TOKEN_OPERADOR, "-");
        }

        if (c == '<' || c == '>') {
            char op[3] = {c, '\0', '\0'};
            int prox = fgetc(arquivo);
            if (prox == '=') op[1] = '='; else ungetc(prox, arquivo);
            return criar_token(TOKEN_OPERADOR, op);
        }
        
        if (c == '*') return criar_token(TOKEN_OPERADOR, "*");

        if (c == '"') {
            char buffer[100]; int i = 0;
            while ((c = fgetc(arquivo)) != '"' && c != EOF && i < 99) buffer[i++] = c;
            buffer[i] = '\0';
            return criar_token(TOKEN_CADEIA, buffer);
        }

        if (isdigit(c)) {
            char buffer[100]; int i = 0;
            buffer[i++] = c;
            while ((isdigit(c = fgetc(arquivo)) || c == '.') && i < 99) buffer[i++] = c;
            ungetc(c, arquivo);
            buffer[i] = '\0';
            return criar_token(TOKEN_VALOR, buffer);
        }

        if (isalpha(c)) {
            char buffer[100]; int i = 0;
            buffer[i++] = c;
            while (isalnum(c = fgetc(arquivo)) && i < 99) buffer[i++] = c;
            ungetc(c, arquivo);
            buffer[i] = '\0';

            if (strcmp(buffer, "inicio") == 0) return criar_token(TOKEN_INICIO, "inicio");
            if (strcmp(buffer, "inteiro") == 0) return criar_token(TOKEN_INTEIRO, "inteiro");
            if (strcmp(buffer, "real") == 0) return criar_token(TOKEN_REAL, "real");
            if (strcmp(buffer, "constante") == 0) return criar_token(TOKEN_CONSTANTE, "constante");
            if (strcmp(buffer, "se") == 0) return criar_token(TOKEN_SE, "se");
            if (strcmp(buffer, "senao") == 0) return criar_token(TOKEN_SENAO, "senao");
            if (strcmp(buffer, "enquanto") == 0) return criar_token(TOKEN_ENQUANTO, "enquanto");
            if (strcmp(buffer, "exibir") == 0) return criar_token(TOKEN_EXIBIR, "exibir");
            if (strcmp(buffer, "ler") == 0) return criar_token(TOKEN_LER, "ler");
            if (strcmp(buffer, "ligar") == 0) return criar_token(TOKEN_LIGAR, "ligar");
            if (strcmp(buffer, "desligar") == 0) return criar_token(TOKEN_DESLIGAR, "desligar");
            if (strcmp(buffer, "esperar") == 0) return criar_token(TOKEN_ESPERAR, "esperar");
            if (strcmp(buffer, "retorne") == 0) return criar_token(TOKEN_RETORNE, "retorne");
            if (strcmp(buffer, "para") == 0) return criar_token(TOKEN_PARA, "para"); // Já adicionei o PARA!

            return criar_token(TOKEN_IDENTIFICADOR, buffer);
        }
    }
    return criar_token(TOKEN_FIM, "");
}