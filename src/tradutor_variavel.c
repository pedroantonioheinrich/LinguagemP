#include <stdio.h>
#include <string.h>
#include "tradutores.h"
#include "lexico.h"
#include "gerador.h"
#include "semantico.h"

extern Token token_atual;

/**
 * Traduz declarações de variáveis, incluindo tipos básicos, registros,
 * ponteiros, vetores e matrizes.
 */
void traduzir_declaracao_variavel() {
    char tipo_c[50];
    char nome_original[256];
    
    // Identifica o tipo base
    if (token_atual.tipo == TOKEN_INTEIRO) strcpy(tipo_c, "int");
    else if (token_atual.tipo == TOKEN_REAL) strcpy(tipo_c, "double");
    else if (token_atual.tipo == TOKEN_CADEIA) strcpy(tipo_c, "char*");
    else if (token_atual.tipo == TOKEN_LOGICO) strcpy(tipo_c, "bool");
    else strcpy(tipo_c, token_atual.lexema); // Tipo customizado (Registro)

    proximo();

    // Suporte a ponteiros (ex: inteiro* ptr)
    while (token_atual.tipo == TOKEN_ASTERISCO) {
        strcat(tipo_c, "*");
        proximo();
    }

    strcpy(nome_original, token_atual.lexema);
    consumir(TOKEN_IDENTIFICADOR, "Esperado nome da variavel");

    gerador_escrever_formatado("%s %s", tipo_c, nome_original);

    // Suporte a Declaração de Matrizes/Vetores (ex: mat[3][3])
    while (token_atual.tipo == TOKEN_ABRE_COLCHETE) {
        gerador_escrever("[");
        proximo();
        gerador_escrever(token_atual.lexema); // Tamanho da dimensão
        proximo(); 
        consumir(TOKEN_FECHA_COLCHETE, "Esperado ']'");
        gerador_escrever("]");
    }

    // Inicialização na declaração (ex: inteiro x = 10;)
    if (token_atual.tipo == TOKEN_ATRIBUICAO) {
        gerador_escrever(" = ");
        proximo();
        traduzir_expressao_ate(TOKEN_PONTO_VIRGULA);
    }
}

/**
 * Traduz acessos a identificadores com suporte recursivo a matrizes e membros de registros.
 * Resolve: lista[0].membro, matriz[i][j], registro.subregistro.campo, ou funcoes()
 */
void traduzir_acesso_identificador(const char* nome, int escopo_atual) {
    (void)escopo_atual;
    gerador_escrever(nome);

    // Loop para permitir acessos encadeados complexos
    while (token_atual.tipo == TOKEN_ABRE_COLCHETE || 
           token_atual.tipo == TOKEN_PONTO || 
           token_atual.tipo == TOKEN_SETA ||
           token_atual.tipo == TOKEN_ABRE_PARENTESES) {
        
        if (token_atual.tipo == TOKEN_ABRE_COLCHETE) {
            gerador_escrever("[");
            proximo();
            traduzir_expressao_ate(TOKEN_FECHA_COLCHETE);
            gerador_escrever("]");
            proximo(); // consome ']'
        } 
        else if (token_atual.tipo == TOKEN_PONTO) {
            gerador_escrever(".");
            proximo();
            gerador_escrever(token_atual.lexema);
            proximo(); // consome nome do membro, volta para o while para ver se tem [i]
        } 
        else if (token_atual.tipo == TOKEN_SETA) {
            gerador_escrever("->");
            proximo();
            gerador_escrever(token_atual.lexema);
            proximo(); // consome nome do membro
        }
        else if (token_atual.tipo == TOKEN_ABRE_PARENTESES) {
            // Suporte para chamadas de função pura (Testes 36 e 59)
            gerador_escrever("(");
            proximo();
            if (token_atual.tipo != TOKEN_FECHA_PARENTESES) {
                traduzir_expressao_ate(TOKEN_FECHA_PARENTESES);
            }
            gerador_escrever(")");
            proximo(); // consome ')'
        }
    }

    // Atribuição (ex: x = 10 ou mat[i][j] = 5)
    if (token_atual.tipo == TOKEN_ATRIBUICAO) {
        gerador_escrever(" = ");
        proximo();
        // Traduz até o final da instrução
        traduzir_expressao_ate(TOKEN_PONTO_VIRGULA);
    }
}