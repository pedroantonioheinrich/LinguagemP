#include <stdio.h>
#include <string.h>
#include "gerador.h"

static FILE* arquivo_saida;
static int ultimo_foi_g = 0;

void gerador_abrir(const char* nome_arquivo) {
    arquivo_saida = fopen(nome_arquivo, "w");
}

void gerador_escrever(const char* texto) {
    if (arquivo_saida) {
        fprintf(arquivo_saida, "%s", texto);
        if (strstr(texto, "printf(\"%g\\n\"") != NULL) {
            ultimo_foi_g = 1;
        } else if (strcmp(texto, ";\n    ") == 0) {
            // Se terminamos um comando, resetamos o estado
        }
    }
}

int gerador_ultimo_foi_g() {
    int status = ultimo_foi_g;
    ultimo_foi_g = 0; 
    return status;
}

void gerador_fechar() {
    if (arquivo_saida) {
        fclose(arquivo_saida);
    }
}