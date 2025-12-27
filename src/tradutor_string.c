#include <stdio.h>
#include <string.h>
#include "tradutores.h"
#include "lexico.h"
#include "gerador.h"
#include "semantico.h"

extern Token token_atual;

/* * Traduz o comando 'exibir' para 'printf'.
 * Identifica se o conteúdo é uma string literal, variável simples ou campo de registro.
 */
void traduzir_comando_exibir() {
    proximo(); // Consome 'exibir'
    consumir(TOKEN_ABRE_PARENTESES, "Esperado '(' apos exibir");

    // Por enquanto, assumimos um printf genérico. 
    // Em uma versão mais avançada, verificaríamos o tipo no semântico para usar %d, %f ou %s.
    gerador_escrever("printf(");

    // Se o que estiver dentro for uma string literal "..."
    if (token_atual.tipo == TOKEN_VALOR_CADEIA) {
        gerador_escrever(token_atual.lexema);
        proximo();
    } 
    // Se for uma variável ou expressão, tratamos via tradutor de expressão
    else {
        // Para simplificar a tradução de P para C, usamos %g para números (formato geral)
        gerador_escrever("\"%g\", "); 
        traduzir_expressao_ate(TOKEN_FECHA_PARENTESES);
    }

    gerador_escrever(")");
    consumir(TOKEN_FECHA_PARENTESES, "Esperado ')' apos os argumentos de exibir");
}

/*
 * Traduz literais de cadeia garantindo que as aspas sejam mantidas.
 */
void traduzir_literal_cadeia(const char* texto) {
    gerador_escrever("\"");
    gerador_escrever(texto);
    gerador_escrever("\"");
}