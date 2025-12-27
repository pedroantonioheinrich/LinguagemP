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
    TOKEN_LOGICO,
    TOKEN_VAZIO,
    TOKEN_SE,
    TOKEN_SENAO,
    TOKEN_ENQUANTO,
    TOKEN_PARA,
    TOKEN_DE,           // Adicionado para: para (i de 1 ate 10)
    TOKEN_ATE,          // Adicionado para: para (i de 1 ate 10)
    TOKEN_RETORNO,
    TOKEN_FUNCAO,
    TOKEN_REGISTRO,
    TOKEN_EXIBIR,
    TOKEN_LER,
    TOKEN_VERDADEIRO,
    TOKEN_FALSO,

    // Operadores e Pontuação
    TOKEN_ATRIBUICAO,       // =
    TOKEN_MAIS,             // +
    TOKEN_MENOS,            // -
    TOKEN_ASTERISCO,        // *
    TOKEN_BARRA,            // /
    TOKEN_PERCENTUAL,       // % (Adicionado para teste 28.lp)
    TOKEN_MAIS_MAIS,        // ++ 
    TOKEN_MENOS_MENOS,      // -- (Adicionado para testes 1.lp, 48.lp)
    TOKEN_E_COMERCIAL,      // &
    TOKEN_PONTO,            // .
    TOKEN_SETA,             // ->
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
    TOKEN_E_LOGICO,         // "e" ou "&&"
    TOKEN_OU_LOGICO,        // "ou" ou "||"
    TOKEN_NAO_LOGICO,       // "nao" ou "!"

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

Token proximo_token(FILE* arquivo);
const char* tipo_token_para_string(TipoToken tipo);

#endif