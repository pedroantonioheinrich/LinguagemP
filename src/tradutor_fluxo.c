#include <stdio.h>
#include <string.h>
#include "tradutores.h"
#include "lexico.h"
#include "gerador.h"
#include "semantico.h"

extern Token token_atual;

/**
 * Traduz o início de uma estrutura condicional 'se'
 * P: se (expressao) { ... } -> C: if (expressao) { ... }
 */
void traduzir_inicio_se() {
    gerador_escrever("if (");
    proximo(); // Consome 'se'
    
    consumir(TOKEN_ABRE_PARENTESES, "Esperado '(' apos o comando 'se'");
    
    // Delega a tradução da condição para o módulo de expressões
    traduzir_expressao_ate(TOKEN_FECHA_PARENTESES);
    
    gerador_escrever(") ");
    consumir(TOKEN_FECHA_PARENTESES, "Esperado ')' apos a condicao do 'se'");
    
    // O sintatico.c chamará bloco() em seguida, que usa o formatador para as chaves
}

/**
 * Traduz o início de um ciclo 'enquanto'
 * P: enquanto (expressao) { ... } -> C: while (expressao) { ... }
 */
void traduzir_inicio_enquanto() {
    gerador_escrever("while (");
    proximo(); // Consome 'enquanto'
    
    consumir(TOKEN_ABRE_PARENTESES, "Esperado '(' apos o comando 'enquanto'");
    
    // Delega a tradução da condição para o módulo de expressões
    traduzir_expressao_ate(TOKEN_FECHA_PARENTESES);
    
    gerador_escrever(") ");
    consumir(TOKEN_FECHA_PARENTESES, "Esperado ')' apos a condicao do 'enquanto'");
    
    // O sintatico.c chamará bloco() em seguida
}

/**
 * Traduz o comando de retorno de funções
 * P: retorno x; -> C: return x;
 */
void traduzir_comando_retorno() {
    gerador_escrever("return ");
    proximo(); // Consome 'retorno'
    
    // Traduz o que vem depois até ao fim da instrução
    traduzir_expressao_ate(TOKEN_PONTO_VIRGULA);
    
    // O ponto e vírgula será inserido pelo formatador_finalizar_instrucao() no sintatico.c
}