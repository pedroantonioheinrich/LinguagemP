#ifndef LEXICO_H
#define LEXICO_H

typedef enum {
    // Tipos de Dados e Variáveis
    TOKEN_INTEIRO,
    TOKEN_REAL,
    TOKEN_CADEIA,
    TOKEN_IDENTIFICADOR,
    TOKEN_NUMERO,       // Adicionado para suportar constantes numéricas explicitamente
    
    // Palavras-Chave de Controle
    TOKEN_INICIO,
    TOKEN_FUNCAO,
    TOKEN_REGISTRO,
    TOKEN_RETORNE,
    TOKEN_SE,
    TOKEN_SENAO,
    TOKEN_ENQUANTO,
    TOKEN_PARA,
    
    // Operadores Lógicos (V11.0)
    TOKEN_E,            // Para o comando "E"
    TOKEN_OU,           // Para o comando "OU"
    TOKEN_NAO,          // Para o comando "NAO"
    
    // Comandos de I/O
    TOKEN_EXIBIR,
    TOKEN_LER,
    
    // Operadores e Pontuação
    TOKEN_ATRIBUICAO,   // =
    TOKEN_IGUAL,        // == (usado internamente na tradução)
    TOKEN_OPERADOR,     // +, -, *, /, ., etc.
    TOKEN_VIRGULA,
    TOKEN_PONTO_VIRGULA,
    TOKEN_ABRE_PARENTESES,
    TOKEN_FECHA_PARENTESES,
    TOKEN_ABRE_CHAVE,
    TOKEN_FECHA_CHAVE,
    TOKEN_ABRE_COLCHETE,
    TOKEN_FECHA_COLCHETE,
    
    // Fim de Arquivo
    TOKEN_FIM,
    TOKEN_ERRO
} TipoToken;

typedef struct {
    TipoToken tipo;
    char lexema[100];
    int linha;
} Token;

#include <stdio.h>
Token proximo_token(FILE* arquivo);

#endif