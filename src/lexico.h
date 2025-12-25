#ifndef LEXICO_H
#define LEXICO_H

#include <stdio.h>

typedef enum {
    // --- Controle e Erros ---
    TOKEN_FIM, 
    TOKEN_ERRO, 

    // --- Palavras-Chave (Fluxo e Tipos) ---
    TOKEN_INICIO, 
    TOKEN_INTEIRO, 
    TOKEN_REAL,
    TOKEN_SE, 
    TOKEN_SENAO, 
    TOKEN_ENQUANTO, 
    TOKEN_PARA,          // Novo: Versão 1.1
    TOKEN_EXIBIR, 
    TOKEN_LER,
    TOKEN_LIGAR, 
    TOKEN_DESLIGAR, 
    TOKEN_ESPERAR, 
    TOKEN_RETORNE, 
    TOKEN_CONSTANTE,
    TOKEN_FUNCAO, 
    TOKEN_SEMPRE,

    // --- Identificadores e Literais ---
    TOKEN_IDENTIFICADOR, 
    TOKEN_VALOR, 
    TOKEN_CADEIA, 

    // --- Operadores e Símbolos ---
    TOKEN_ATRIBUICAO,         // =
    TOKEN_MAIS_IGUAL,         // += (Novo: Versão 1.1)
    TOKEN_MENOS_IGUAL,        // -= (Novo: Versão 1.1)
    TOKEN_OPERADOR,           // +, -, *, /, %, ==, !=, <, >, <=, >=
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

// Protótipo da função principal do léxico
Token proximo_token(FILE* arquivo);

#endif