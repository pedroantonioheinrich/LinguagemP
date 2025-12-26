#ifndef LEXICO_H
#define LEXICO_H

#include <stdio.h>

typedef enum {
    // Palavras-chave
    TOKEN_INICIO,
    TOKEN_FIM,
    TOKEN_INTEIRO,
    TOKEN_REAL,
    TOKEN_CADEIA,
    TOKEN_LOGICO,      // Novo: tipo booleano
    TOKEN_VAZIO,
    TOKEN_SE,
    TOKEN_SENAO,
    TOKEN_ENQUANTO,
    TOKEN_RETORNO,
    TOKEN_FUNCAO,
    TOKEN_REGISTRO,
    TOKEN_EXIBIR,
    TOKEN_VERDADEIRO,  // Novo: literal true
    TOKEN_FALSO,       // Novo: literal false

    // Operadores e Pontuação
    TOKEN_ATRIBUICAO,       // =
    TOKEN_MAIS,             // +
    TOKEN_MENOS,            // -
    TOKEN_ASTERISCO,        // *
    TOKEN_BARRA,            // /
    TOKEN_E_COMERCIAL,      // &
    TOKEN_PONTO,            // .
    TOKEN_SETA,             // -> (Adicionado para açúcar sintático de ponteiros)
    TOKEN_VIRGULA,          // ,
    TOKEN_PONTO_VIRGULA,    // ;
    TOKEN_ABRE_PARENTESES,  // (
    TOKEN_FECHA_PARENTESES, // )
    TOKEN_ABRE_CHAVE,       // {
    TOKEN_FECHA_CHAVE,      // }
    TOKEN_ABRE_COLCHETE,    // [
    TOKEN_FECHA_COLCHETE,   // ]
    
    // Operadores Relacionais e Lógicos
    TOKEN_IGUAL_IGUAL,      // ==
    TOKEN_DIFERENTE,        // !=
    TOKEN_MENOR,            // <
    TOKEN_MAIOR,            // >
    TOKEN_MENOR_IGUAL,      // <=
    TOKEN_MAIOR_IGUAL,      // >=
    TOKEN_E_LOGICO,         // "e"
    TOKEN_OU_LOGICO,        // "ou"
    TOKEN_NAO_LOGICO,       // "nao"

    // Literais e Identificadores
    TOKEN_IDENTIFICADOR,
    TOKEN_VALOR_INTEIRO,
    TOKEN_VALOR_REAL,
    TOKEN_VALOR_CADEIA,

    // Controle
    TOKEN_ERRO,
    TOKEN_EOF
} TipoToken;

typedef struct {
    TipoToken tipo;
    char lexema[256];
    int linha;
} Token;

// --- PROTÓTIPOS ---

/**
 * Obtém o próximo token do arquivo fonte.
 */
Token proximo_token(FILE* arquivo);

/**
 * Converte o enum TipoToken para uma representação em string.
 * Útil para logs, depuração e verificação de tipos no sintático.
 */
const char* tipo_token_para_string(TipoToken tipo);

#endif