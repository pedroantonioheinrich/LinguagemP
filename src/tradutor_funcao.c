#include <stdio.h>
#include <string.h>
#include "tradutores.h"
#include "lexico.h"
#include "gerador.h"
#include "sintatico.h"

extern Token token_atual;

// Protótipo da função definida no sintatico.c para evitar erro de compilação
Token espiar();

/**
 * Traduz declarações de funções.
 * Suporta: funcao tipo nome() e funcao nome() (neste caso assume void).
 */
void traduzir_declaracao_funcao() {
    proximo(); // consome 'funcao'
    
    char tipo_c[50];
    char nome_funcao[256];

    // 1. Identifica o tipo de retorno ou assume void
    // Suporte para TOKEN_IDENTIFICADOR como tipo de retorno (Registros/Structs)
    if (token_atual.tipo == TOKEN_INTEIRO || token_atual.tipo == TOKEN_REAL || 
        token_atual.tipo == TOKEN_CADEIA || token_atual.tipo == TOKEN_LOGICO || 
        token_atual.tipo == TOKEN_VAZIO || (token_atual.tipo == TOKEN_IDENTIFICADOR && espiar().tipo == TOKEN_IDENTIFICADOR)) {
        
        if (token_atual.tipo == TOKEN_INTEIRO) strcpy(tipo_c, "int");
        else if (token_atual.tipo == TOKEN_REAL) strcpy(tipo_c, "double");
        else if (token_atual.tipo == TOKEN_CADEIA) strcpy(tipo_c, "char*");
        else if (token_atual.tipo == TOKEN_LOGICO) strcpy(tipo_c, "bool");
        else if (token_atual.tipo == TOKEN_VAZIO) strcpy(tipo_c, "void");
        else strcpy(tipo_c, token_atual.lexema); // Nome do Registro (Ex: Usuario)
        
        proximo(); // consome o tipo
        strcpy(nome_funcao, token_atual.lexema);
        proximo(); // consome o nome
    } else {
        // Assume void se vier direto o identificador do nome da função
        strcpy(tipo_c, "void");
        strcpy(nome_funcao, token_atual.lexema);
        proximo(); // consome o nome
    }
    
    gerador_escrever_formatado("%s %s(", tipo_c, nome_funcao);
    consumir(TOKEN_ABRE_PARENTESES, "Esperado '(' apos nome da funcao");
    
    // 2. Tradução dos Parâmetros
    while (token_atual.tipo != TOKEN_FECHA_PARENTESES && token_atual.tipo != TOKEN_EOF) {
        char tipo_p[50];
        
        // Identifica o tipo do parâmetro
        if (token_atual.tipo == TOKEN_INTEIRO) strcpy(tipo_p, "int");
        else if (token_atual.tipo == TOKEN_REAL) strcpy(tipo_p, "double");
        else if (token_atual.tipo == TOKEN_CADEIA) strcpy(tipo_p, "char*");
        else if (token_atual.tipo == TOKEN_LOGICO) strcpy(tipo_p, "bool");
        else if (token_atual.tipo == TOKEN_VAZIO) strcpy(tipo_p, "void");
        else if (token_atual.tipo == TOKEN_IDENTIFICADOR) strcpy(tipo_p, token_atual.lexema);
        else strcpy(tipo_p, "int"); 
        
        proximo(); // consome o tipo
        
        // Suporte a ponteiros nos parâmetros (ex: Usuario* p)
        while (token_atual.tipo == TOKEN_ASTERISCO) {
            strcat(tipo_p, "*");
            proximo();
        }
        
        // Escreve tipo e nome do parâmetro
        gerador_escrever_formatado("%s %s", tipo_p, token_atual.lexema);
        consumir(TOKEN_IDENTIFICADOR, "Esperado nome do parametro");
        
        if (token_atual.tipo == TOKEN_VIRGULA) {
            gerador_escrever(", ");
            proximo();
        }
    }
    
    gerador_escrever(") ");
    consumir(TOKEN_FECHA_PARENTESES, "Esperado ')' apos parametros");
    
    // 3. Corpo da Função
    bloco(); 
    gerador_escrever("\n");
}