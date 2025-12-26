#ifndef LEXICO_H
#define LEXICO_H

#include <stdio.h>

typedef enum {
    // Tipos e Valores
    TOKEN_INTEIRO, TOKEN_REAL, TOKEN_CADEIA,
    TOKEN_IDENTIFICADOR, 
    TOKEN_VALOR_INTEIRO, TOKEN_VALOR_REAL,
    
    // Operadores e Pontuação
    TOKEN_ATRIBUICAO,   // =
    TOKEN_OPERADOR,     // +, -, *, /
    TOKEN_PONTO_VIRGULA, // ;
    TOKEN_ABRE_PARENTESES, TOKEN_FECHA_PARENTESES,
    TOKEN_ABRE_CHAVE, TOKEN_FECHA_CHAVE,
    TOKEN_ABRE_COLCHETE, TOKEN_FECHA_COLCHETE,
    TOKEN_VIRGULA, 
    TOKEN_PONTO,        // Para acesso a registro: p1.nome
    
    // Palavras-chave de Controle
    TOKEN_SE, TOKEN_SENAO, TOKEN_ENQUANTO, TOKEN_PARA,
    TOKEN_DE, TOKEN_ATE,
    
    // I/O e Comandos
    TOKEN_EXIBIR, TOKEN_LEIA,
    
    // Estruturas de Dados e Funções
    TOKEN_FUNCAO, TOKEN_RETORNO, TOKEN_REGISTRO,
    
    // Delimitadores de Programa
    TOKEN_INICIO, TOKEN_FIM,
    
    // Especial
    TOKEN_ERRO
} TipoToken;

typedef struct {
    TipoToken tipo;
    char lexema[100];
    int linha;
} Token;

// Função principal do Analisador Léxico
Token proximo_token(FILE* arquivo);

#endif