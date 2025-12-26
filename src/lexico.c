#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "lexico.h"

int linha_atual = 1;

const char* tipo_token_para_string(TipoToken tipo) {
    switch (tipo) {
        case TOKEN_INICIO: return "INICIO";
        case TOKEN_FIM: return "FIM";
        case TOKEN_INTEIRO: return "INTEIRO";
        case TOKEN_REAL: return "REAL";
        case TOKEN_CADEIA: return "CADEIA";
        case TOKEN_LOGICO: return "LOGICO";
        case TOKEN_VAZIO: return "VAZIO";
        case TOKEN_SE: return "SE";
        case TOKEN_SENAO: return "SENAO";
        case TOKEN_ENQUANTO: return "ENQUANTO";
        case TOKEN_RETORNO: return "RETORNO";
        case TOKEN_FUNCAO: return "FUNCAO";
        case TOKEN_REGISTRO: return "REGISTRO";
        case TOKEN_EXIBIR: return "EXIBIR";
        case TOKEN_VERDADEIRO: return "VERDADEIRO";
        case TOKEN_FALSO: return "FALSO";
        case TOKEN_IDENTIFICADOR: return "IDENTIFICADOR";
        case TOKEN_VALOR_INTEIRO: return "VALOR_INTEIRO";
        case TOKEN_VALOR_REAL: return "VALOR_REAL";
        case TOKEN_VALOR_CADEIA: return "VALOR_CADEIA";
        case TOKEN_ASTERISCO: return "ASTERISCO";
        case TOKEN_E_COMERCIAL: return "E_COMERCIAL";
        case TOKEN_PONTO_VIRGULA: return "PONTO_VIRGULA";
        case TOKEN_ABRE_PARENTESES: return "ABRE_PARENTESES";
        case TOKEN_FECHA_PARENTESES: return "FECHA_PARENTESES";
        case TOKEN_ABRE_CHAVE: return "ABRE_CHAVE";
        case TOKEN_FECHA_CHAVE: return "FECHA_CHAVE";
        case TOKEN_ABRE_COLCHETE: return "ABRE_COLCHETE";
        case TOKEN_FECHA_COLCHETE: return "FECHA_COLCHETE";
        case TOKEN_IGUAL_IGUAL: return "IGUAL_IGUAL";
        case TOKEN_DIFERENTE: return "DIFERENTE";
        case TOKEN_MENOR: return "MENOR";
        case TOKEN_MAIOR: return "MAIOR";
        case TOKEN_MENOR_IGUAL: return "MENOR_IGUAL";
        case TOKEN_MAIOR_IGUAL: return "MAIOR_IGUAL";
        case TOKEN_E_LOGICO: return "E_LOGICO";
        case TOKEN_OU_LOGICO: return "OU_LOGICO";
        case TOKEN_NAO_LOGICO: return "NAO_LOGICO";
        case TOKEN_ATRIBUICAO: return "ATRIBUICAO";
        case TOKEN_VIRGULA: return "VIRGULA";
        case TOKEN_PONTO: return "PONTO";
        case TOKEN_MAIS: return "MAIS";
        case TOKEN_MENOS: return "MENOS";
        case TOKEN_BARRA: return "BARRA";
        case TOKEN_SETA: return "SETA"; // Adicionado para auditoria
        case TOKEN_EOF: return "EOF";
        default: return "OUTRO/ERRO";
    }
}

Token proximo_token(FILE* arquivo) {
    int c;
    Token t;
    
    while (1) {
        c = fgetc(arquivo);
        if (c == EOF) {
            t.tipo = TOKEN_EOF;
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
    memset(t.lexema, 0, 256);
    int i = 0;

    if (isalpha(c) || c == '_') {
        while (isalnum(c) || c == '_') {
            if (i < 255) t.lexema[i++] = c;
            c = fgetc(arquivo);
        }
        ungetc(c, arquivo);
        t.lexema[i] = '\0';
        
        if (strcmp(t.lexema, "inteiro") == 0) t.tipo = TOKEN_INTEIRO;
        else if (strcmp(t.lexema, "real") == 0) t.tipo = TOKEN_REAL;
        else if (strcmp(t.lexema, "cadeia") == 0) t.tipo = TOKEN_CADEIA;
        else if (strcmp(t.lexema, "logico") == 0) t.tipo = TOKEN_LOGICO;
        else if (strcmp(t.lexema, "vazio") == 0) t.tipo = TOKEN_VAZIO;
        else if (strcmp(t.lexema, "se") == 0) t.tipo = TOKEN_SE;
        else if (strcmp(t.lexema, "senao") == 0) t.tipo = TOKEN_SENAO;
        else if (strcmp(t.lexema, "enquanto") == 0) t.tipo = TOKEN_ENQUANTO;
        else if (strcmp(t.lexema, "exibir") == 0) t.tipo = TOKEN_EXIBIR;
        else if (strcmp(t.lexema, "funcao") == 0) t.tipo = TOKEN_FUNCAO;
        else if (strcmp(t.lexema, "retorno") == 0) t.tipo = TOKEN_RETORNO;
        else if (strcmp(t.lexema, "registro") == 0) t.tipo = TOKEN_REGISTRO;
        else if (strcmp(t.lexema, "inicio") == 0) t.tipo = TOKEN_INICIO;
        else if (strcmp(t.lexema, "verdadeiro") == 0) t.tipo = TOKEN_VERDADEIRO;
        else if (strcmp(t.lexema, "falso") == 0) t.tipo = TOKEN_FALSO;
        else if (strcmp(t.lexema, "e") == 0) t.tipo = TOKEN_E_LOGICO;
        else if (strcmp(t.lexema, "ou") == 0) t.tipo = TOKEN_OU_LOGICO;
        else if (strcmp(t.lexema, "nao") == 0) t.tipo = TOKEN_NAO_LOGICO;
        else t.tipo = TOKEN_IDENTIFICADOR;
        return t;
    }

    if (isdigit(c)) {
        int eh_real = 0;
        while (isdigit(c) || c == '.') {
            if (c == '.') eh_real = 1;
            if (i < 255) t.lexema[i++] = c;
            c = fgetc(arquivo);
        }
        ungetc(c, arquivo);
        t.lexema[i] = '\0';
        t.tipo = eh_real ? TOKEN_VALOR_REAL : TOKEN_VALOR_INTEIRO;
        return t;
    }

    if (c == '"') {
        t.lexema[i++] = c;
        while ((c = fgetc(arquivo)) != '"' && c != EOF) {
            if (c == '\n') linha_atual++;
            if (i < 254) t.lexema[i++] = c;
        }
        if (c == '"') t.lexema[i++] = '"';
        t.lexema[i] = '\0';
        t.tipo = TOKEN_VALOR_CADEIA;
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
        case '!':
            c = fgetc(arquivo);
            if (c == '=') { strcpy(t.lexema, "!="); t.tipo = TOKEN_DIFERENTE; }
            else { ungetc(c, arquivo); t.tipo = TOKEN_ERRO; } 
            break;
        case '<':
            c = fgetc(arquivo);
            if (c == '=') { strcpy(t.lexema, "<="); t.tipo = TOKEN_MENOR_IGUAL; }
            else { ungetc(c, arquivo); t.tipo = TOKEN_MENOR; }
            break;
        case '>':
            c = fgetc(arquivo);
            if (c == '=') { strcpy(t.lexema, ">="); t.tipo = TOKEN_MAIOR_IGUAL; }
            else { ungetc(c, arquivo); t.tipo = TOKEN_MAIOR; }
            break;
        case '+': t.tipo = TOKEN_MAIS; break;
        case '-': 
            c = fgetc(arquivo);
            if (c == '>') { // Identifica o operador de seta ->
                strcpy(t.lexema, "->");
                t.tipo = TOKEN_SETA;
            } else {
                ungetc(c, arquivo);
                t.tipo = TOKEN_MENOS;
            }
            break;
        case '*': t.tipo = TOKEN_ASTERISCO; break;
        case '/': t.tipo = TOKEN_BARRA; break;
        case '&': t.tipo = TOKEN_E_COMERCIAL; break;
        case ';': t.tipo = TOKEN_PONTO_VIRGULA; break;
        case '(': t.tipo = TOKEN_ABRE_PARENTESES; break;
        case ')': t.tipo = TOKEN_FECHA_PARENTESES; break;
        case '{': t.tipo = TOKEN_ABRE_CHAVE; break;
        case '}': t.tipo = TOKEN_FECHA_CHAVE; break;
        case '[': t.tipo = TOKEN_ABRE_COLCHETE; break;
        case ']': t.tipo = TOKEN_FECHA_COLCHETE; break;
        case ',': t.tipo = TOKEN_VIRGULA; break;
        case '.': t.tipo = TOKEN_PONTO; break;
        default:  t.tipo = TOKEN_ERRO; break;
    }
    return t;
}