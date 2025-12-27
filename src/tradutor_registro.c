#include <stdio.h>
#include <string.h>
#include "tradutores.h"
#include "lexico.h"
#include "gerador.h"

extern Token token_atual;

/**
 * Traduz a definição de um registro (struct) para C.
 * Suporta membros de tipos básicos, vetores e outros registros.
 */
void traduzir_definicao_registro() {
    proximo(); // consome 'registro'
    char nome_reg[256];
    strcpy(nome_reg, token_atual.lexema);
    proximo(); // consome o nome do identificador do registro
    
    // Usamos typedef struct para facilitar a declaração posterior no C
    gerador_escrever_formatado("typedef struct {\n");
    consumir(TOKEN_ABRE_CHAVE, "Esperado '{' para iniciar o corpo do registro");
    
    while (token_atual.tipo != TOKEN_FECHA_CHAVE && token_atual.tipo != TOKEN_EOF) {
        formatador_indentar();
        
        // Traduz a declaração do membro (ex: inteiro id)
        traduzir_declaracao_variavel();
        
        // Garante que o membro termine com ';' no C gerado
        gerador_escrever(";\n");

        // Se houver um ';' opcional no código fonte da Linguagem P, nós o consumimos
        if (token_atual.tipo == TOKEN_PONTO_VIRGULA) {
            proximo();
        }
    }
    
    consumir(TOKEN_FECHA_CHAVE, "Esperado '}' para fechar o registro");
    
    // Define o nome da struct no final para fechar o typedef
    gerador_escrever_formatado("} %s;\n\n", nome_reg);
}