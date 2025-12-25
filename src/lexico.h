#ifndef LEXICO_H
#define LEXICO_H

#include <stdio.h>

typedef enum {
    // Tokens de Controle e Pontuação
    TOKEN_INICIO,
    TOKEN_FIM,
    TOKEN_ABRE_PARENTESES,
    TOKEN_FECHA_PARENTESES,
    TOKEN_ABRE_CHAVE,
    TOKEN_FECHA_CHAVE,
    TOKEN_PONTO_VIRGULA,
    TOKEN_VIRGULA,

    // Tipos de Dados e Identificadores
    TOKEN_INTEIRO,
    TOKEN_REAL,
    TOKEN_CADEIA,
    TOKEN_IDENTIFICADOR,
    TOKEN_VALOR,
    TOKEN_CONSTANTE,

    // Palavras-Chave de Comandos
    TOKEN_EXIBIR,
    TOKEN_LER,
    TOKEN_FUNCAO,
    TOKEN_RETORNE,
    TOKEN_LIGAR,
    TOKEN_DESLIGAR,
    TOKEN_ESPERAR,
    TOKEN_PARA,
    TOKEN_DE,
    TOKEN_ATE,

    // Estruturas de Controle (Novos v1.5)
    TOKEN_SE,
    TOKEN_SENAO,
    TOKEN_ENQUANTO,

    // Operadores e Atribuição
    TOKEN_ATRIBUICAO,   // =
    TOKEN_OPERADOR,     // +, -, *, /, %
    TOKEN_MAIS_IGUAL,   // +=
    TOKEN_MENOS_IGUAL,  // -=

    // Operadores Relacionais (Novos v1.5)
    TOKEN_IGUAL,        // ==
    TOKEN_DIFERENTE,    // !=
    TOKEN_MENOR,        // <
    TOKEN_MAIOR,        // >
    TOKEN_MENOR_IGUAL,  // <=
    TOKEN_MAIOR_IGUAL,  // >=
    
    // Operadores Lógicos
    TOKEN_E,            // &&
    TOKEN_OU            // ||
} TipoToken;

typedef struct {
    TipoToken tipo;
    char lexema[100];
    int linha;
    int coluna;
} Token;

// Variáveis globais para rastreamento de posição
extern int linha_atual;
extern int coluna_atual;

// Protótipos das funções do Léxico
Token proximo_token(FILE *arquivo);
Token criar_token(TipoToken tipo, const char* lexema);

#endif