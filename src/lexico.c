#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "lexico.h"

int linha_atual = 1;

Token proximo_token(FILE* arquivo) {
    int c;
    Token t;
    
    while (1) {
        c = fgetc(arquivo);
        if (c == EOF) {
            t.tipo = TOKEN_FIM;
            strcpy(t.lexema, "EOF");
            t.linha = linha_atual;
            return t;
        }
        if (isspace(c)) {
            if (c == '\n') linha_atual++;
            continue;
        }
        if (c == '/') {
            int proximo = fgetc(arquivo);
            if (proximo == '/') {
                while ((c = fgetc(arquivo)) != '\n' && c != EOF);
                if (c == '\n') linha_atual++;
                continue; 
            } else {
                ungetc(proximo, arquivo);
            }
        }
        break;
    }

    t.linha = linha_atual;
    memset(t.lexema, 0, 100);
    int i = 0;

    if (isalpha(c) || c == '_') {
        while (isalnum(c) || c == '_') {
            if (i < 99) t.lexema[i++] = c;
            c = fgetc(arquivo);
        }
        ungetc(c, arquivo);
        
        if (strcmp(t.lexema, "inteiro") == 0) t.tipo = TOKEN_INTEIRO;
        else if (strcmp(t.lexema, "real") == 0) t.tipo = TOKEN_REAL;
        else if (strcmp(t.lexema, "cadeia") == 0) t.tipo = TOKEN_CADEIA;
        else if (strcmp(t.lexema, "se") == 0) t.tipo = TOKEN_SE;
        else if (strcmp(t.lexema, "senao") == 0) t.tipo = TOKEN_SENAO;
        else if (strcmp(t.lexema, "enquanto") == 0) t.tipo = TOKEN_ENQUANTO;
        else if (strcmp(t.lexema, "para") == 0) t.tipo = TOKEN_PARA;
        else if (strcmp(t.lexema, "de") == 0) t.tipo = TOKEN_DE;
        else if (strcmp(t.lexema, "ate") == 0) t.tipo = TOKEN_ATE;
        else if (strcmp(t.lexema, "exibir") == 0) t.tipo = TOKEN_EXIBIR;
        else if (strcmp(t.lexema, "leia") == 0) t.tipo = TOKEN_LEIA;
        else if (strcmp(t.lexema, "funcao") == 0) t.tipo = TOKEN_FUNCAO;
        else if (strcmp(t.lexema, "retorno") == 0) t.tipo = TOKEN_RETORNO;
        else if (strcmp(t.lexema, "registro") == 0) t.tipo = TOKEN_REGISTRO;
        else if (strcmp(t.lexema, "inicio") == 0) t.tipo = TOKEN_INICIO;
        else if (strcmp(t.lexema, "e") == 0) t.tipo = TOKEN_E;
        else if (strcmp(t.lexema, "ou") == 0) t.tipo = TOKEN_OU;
        else if (strcmp(t.lexema, "nao") == 0) t.tipo = TOKEN_NAO; // NOVO
        else t.tipo = TOKEN_IDENTIFICADOR;
        return t;
    }

    if (isdigit(c)) {
        int eh_real = 0;
        while (isdigit(c) || c == '.') {
            if (c == '.') eh_real = 1;
            if (i < 99) t.lexema[i++] = c;
            c = fgetc(arquivo);
        }
        ungetc(c, arquivo);
        t.tipo = eh_real ? TOKEN_VALOR_REAL : TOKEN_VALOR_INTEIRO;
        return t;
    }

    if (c == '"') {
        t.lexema[i++] = c;
        while ((c = fgetc(arquivo)) != '"' && c != EOF) {
            if (i < 98) t.lexema[i++] = c;
        }
        if (c == '"') t.lexema[i++] = '"';
        t.lexema[i] = '\0';
        t.tipo = TOKEN_CADEIA;
        return t;
    }

    t.lexema[0] = c;
    t.lexema[1] = '\0';
    switch (c) {
        case '=': 
            c = fgetc(arquivo);
            if (c == '=') { strcpy(t.lexema, "=="); t.tipo = TOKEN_IGUAL_IGUAL; }
            else { ungetc(c, arquivo); t.tipo = TOKEN_ATRIBUICAO; }
            break;
        case '>': case '<': case '!':
            {
                int prox = fgetc(arquivo);
                if (prox == '=') { 
                    t.lexema[1] = prox; t.lexema[2] = '\0'; 
                    if (c == '>') t.tipo = TOKEN_MAIOR_IGUAL;
                    else if (c == '<') t.tipo = TOKEN_MENOR_IGUAL;
                    else t.tipo = TOKEN_DIFERENTE;
                } else {
                    ungetc(prox, arquivo);
                    if (c == '>') t.tipo = TOKEN_MAIOR;
                    else if (c == '<') t.tipo = TOKEN_MENOR;
                    else t.tipo = TOKEN_ERRO;
                }
            }
            break;
        case '+': t.tipo = TOKEN_SOMA; break;
        case '-': t.tipo = TOKEN_SUBTRACAO; break;
        case '*': t.tipo = TOKEN_MULTIPLICACAO; break;
        case '/': t.tipo = TOKEN_DIVISAO; break;
        case ';': t.tipo = TOKEN_PONTO_VIRGULA; break;
        case '(': t.tipo = TOKEN_ABRE_PARENTESES; break;
        case ')': t.tipo = TOKEN_FECHA_PARENTESES; break;
        case '{': t.tipo = TOKEN_ABRE_CHAVE; break;
        case '}': t.tipo = TOKEN_FECHA_CHAVE; break;
        case '[': t.tipo = TOKEN_ABRE_COLCHETE; break;
        case ']': t.tipo = TOKEN_FECHA_COLCHETE; break;
        case ',': t.tipo = TOKEN_VIRGULA; break;
        case '.': t.tipo = TOKEN_PONTO; break;
        default: t.tipo = TOKEN_ERRO; break;
    }
    return t;
}