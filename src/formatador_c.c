#include <stdio.h>
#include "tradutores.h"
#include "gerador.h"

static int nivel_indentacao = 0;

/* * Garante que cada instrução termine com ';' e pule para a próxima linha.
 * Isso resolve o erro de comandos grudados.
 */
void formatador_finalizar_instrucao() {
    gerador_escrever(";\n");
    formatador_indentar();
}

/* * Adiciona espaços no início da linha baseados no nível de escopo atual.
 */
void formatador_indentar() {
    for (int i = 0; i < nivel_indentacao; i++) {
        gerador_escrever("    "); // 4 espaços por nível
    }
}

/* * Aumenta o recuo quando entramos em um bloco { }
 */
void traduzir_abrir_bloco() {
    gerador_escrever("{\n");
    nivel_indentacao++;
    formatador_indentar();
}

/* * Diminui o recuo quando fechamos um bloco { }
 */
void traduzir_fechar_bloco() {
    if (nivel_indentacao > 0) nivel_indentacao--;
    gerador_escrever("\n");
    formatador_indentar();
    gerador_escrever("}\n");
    formatador_indentar();
}

/* * Força uma quebra de linha simples sem ponto e vírgula.
 */
void formatador_quebrar_linha() {
    gerador_escrever("\n");
    formatador_indentar();
}