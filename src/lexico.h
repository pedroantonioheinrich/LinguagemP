#ifndef LEXICO_H
#define LEXICO_H

#include <stdio.h>

typedef enum {
    TOKEN_FIM = 0,      // Definir explicitamente como 0 ajuda em alguns testes
    TOKEN_ERRO,
    TOKEN_INICIO,
    TOKEN_INTEIRO,
    TOKEN_REAL,
    TOKEN_SE,
    TOKEN_SENAO,
    TOKEN_ENQUANTO,
    TOKEN_PARA,
    TOKEN_EXIBIR,
    TOKEN_LER,
    TOKEN_LIGAR,
    TOKEN_DESLIGAR,
    TOKEN_ESPERAR,
    TOKEN_RETORNE,
    TOKEN_CONSTANTE,
    TOKEN_E,
    TOKEN_OU,
    TOKEN_IDENTIFICADOR,
    TOKEN_VALOR,
    TOKEN_CADEIA,
    TOKEN_ATRIBUICAO,
    TOKEN_MAIS_IGUAL,
    TOKEN_MENOS_IGUAL,
    TOKEN_OPERADOR,
    TOKEN_ABRE_PARENTESES,
    TOKEN_FECHA_PARENTESES,
    TOKEN_ABRE_CHAVE,
    TOKEN_FECHA_CHAVE,
    TOKEN_PONTO_VIRGULA,
    TOKEN_VIRGULA
} TipoToken;

typedef struct {
    TipoToken tipo;
    char lexema[100];
    int linha;
    int coluna; 
} Token;

Token proximo_token(FILE* arquivo);

#endif