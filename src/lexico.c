#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lexico.h"

Token proximo_token(FILE* arquivo) {
    Token t;
    int c = fgetc(arquivo);

    while (isspace(c)) {
        if (c == '\n') t.linha++;
        c = fgetc(arquivo);
    }

    if (c == EOF) {
        t.tipo = TOKEN_FIM;
        strcpy(t.lexema, "EOF");
        return t;
    }

    if (isalpha(c)) {
        int i = 0;
        while (isalnum(c) || c == '_') {
            t.lexema[i++] = c;
            c = fgetc(arquivo);
        }
        t.lexema[i] = '\0';
        ungetc(c, arquivo);

        if (strcmp(t.lexema, "inicio") == 0) t.tipo = TOKEN_INICIO;
        else if (strcmp(t.lexema, "inteiro") == 0) t.tipo = TOKEN_INTEIRO;
        else if (strcmp(t.lexema, "real") == 0) t.tipo = TOKEN_REAL;
        else if (strcmp(t.lexema, "cadeia") == 0) t.tipo = TOKEN_CADEIA;
        else if (strcmp(t.lexema, "exibir") == 0) t.tipo = TOKEN_EXIBIR;
        else if (strcmp(t.lexema, "ler") == 0) t.tipo = TOKEN_LER;
        else if (strcmp(t.lexema, "se") == 0) t.tipo = TOKEN_SE;
        else if (strcmp(t.lexema, "senao") == 0) t.tipo = TOKEN_SENAO;
        else if (strcmp(t.lexema, "enquanto") == 0) t.tipo = TOKEN_ENQUANTO;
        else if (strcmp(t.lexema, "para") == 0) t.tipo = TOKEN_PARA;
        else if (strcmp(t.lexema, "funcao") == 0) t.tipo = TOKEN_FUNCAO;
        else if (strcmp(t.lexema, "retorne") == 0) t.tipo = TOKEN_RETORNE;
        else if (strcmp(t.lexema, "registro") == 0) t.tipo = TOKEN_REGISTRO;
        // Novos Operadores Lógicos em Maiúsculo
        else if (strcmp(t.lexema, "E") == 0) t.tipo = TOKEN_E;
        else if (strcmp(t.lexema, "OU") == 0) t.tipo = TOKEN_OU;
        else if (strcmp(t.lexema, "NAO") == 0) t.tipo = TOKEN_NAO;
        else t.tipo = TOKEN_IDENTIFICADOR;
        
        return t;
    }

    if (isdigit(c)) {
        int i = 0;
        while (isdigit(c) || c == '.') {
            t.lexema[i++] = c;
            c = fgetc(arquivo);
        }
        t.lexema[i] = '\0';
        ungetc(c, arquivo);
        t.tipo = TOKEN_NUMERO;
        return t;
    }

    t.lexema[0] = c;
    t.lexema[1] = '\0';
    if (c == '=') t.tipo = TOKEN_ATRIBUICAO;
    else if (c == ';') t.tipo = TOKEN_PONTO_VIRGULA;
    else if (c == '(') t.tipo = TOKEN_ABRE_PARENTESES;
    else if (c == ')') t.tipo = TOKEN_FECHA_PARENTESES;
    else if (c == '{') t.tipo = TOKEN_ABRE_CHAVE;
    else if (c == '}') t.tipo = TOKEN_FECHA_CHAVE;
    else if (c == '[') t.tipo = TOKEN_ABRE_COLCHETE;
    else if (c == ']') t.tipo = TOKEN_FECHA_COLCHETE;
    else if (c == ',') t.tipo = TOKEN_VIRGULA;
    else t.tipo = TOKEN_OPERADOR;

    return t;
}