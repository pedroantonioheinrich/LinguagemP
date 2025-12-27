#include <stdio.h>
#include <string.h>
#include "tradutores.h"
#include "lexico.h"
#include "gerador.h"
#include "semantico.h"

extern Token token_atual;

void traduzir_literal_cadeia(const char* texto) {
    gerador_escrever("\"");
    gerador_escrever(texto);
    gerador_escrever("\"");
}

void traduzir_comando_exibir() {
    proximo(); // Consome 'exibir'
    consumir(TOKEN_ABRE_PARENTESES, "Esperado '(' apos exibir");

    if (token_atual.tipo == TOKEN_VALOR_CADEIA) {
        gerador_escrever("printf(");
        traduzir_literal_cadeia(token_atual.lexema);
        proximo();
    } 
    else {
        TipoToken tipo = semantico_obter_tipo(token_atual.lexema);
        
        if (tipo == TOKEN_INTEIRO) {
            gerador_escrever("printf(\"%d\", ");
        } else if (tipo == TOKEN_CADEIA) {
            gerador_escrever("printf(\"%s\", ");
        } else {
            gerador_escrever("printf(\"%g\", "); 
        }
        
        traduzir_expressao_ate(TOKEN_FECHA_PARENTESES);
    }

    gerador_escrever(")");
    consumir(TOKEN_FECHA_PARENTESES, "Esperado ')' apos exibir");
}