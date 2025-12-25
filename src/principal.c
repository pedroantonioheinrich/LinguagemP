#include <stdio.h>
#include "logs.h"
#include "sintatico.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        P_LOG_ERRO("Uso: lp_compilador <arquivo.lp>");
        return 1;
    }

    FILE* f = fopen(argv[1], "r");
    if (!f) {
        P_LOG_HARDWARE("Nao foi possivel abrir o arquivo fonte.");
        return 1;
    }

    P_LOG_INFO("--- Iniciando Compilacao da Linguagem P ---");
    
    // Chama o Analisador Sintático (que por sua vez usa o Léxico)
    analisar(f);

    fclose(f);
    return 0;
}