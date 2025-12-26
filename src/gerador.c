#include <stdio.h>
#include <string.h>
#include "gerador.h"
#include "logs.h"

static FILE* arquivo_saida = NULL;
static int ultimo_foi_g = 0;

void gerador_abrir(const char* nome_arquivo) {
    arquivo_saida = fopen(nome_arquivo, "w");
    if (!arquivo_saida) {
        P_LOG_ERRO("Nao foi possivel abrir o arquivo de saida para geracao de codigo.");
        return;
    }
    #ifdef DEBUG
    printf("[DEBUG] Gerador: Arquivo '%s' aberto com sucesso.\n", nome_arquivo);
    #endif
}

void gerador_escrever(const char* texto) {
    if (arquivo_saida && texto) {
        // Log de Auditoria Física para depuração do açúcar sintático e operadores
        #ifdef DEBUG
        printf("[FILE-WRITE] Escrevendo: '%s'\n", texto);
        #endif

        // Gravamos no arquivo C gerado
        fprintf(arquivo_saida, "%s", texto);
        
        // FORÇAMOS a descarga do buffer para o disco imediatamente.
        // Isso é vital para garantir que, se o compilador der crash no sintatico,
        // o que já foi traduzido (como o nome da variável antes da seta) esteja no arquivo.
        fflush(arquivo_saida);

        // Verifica se o último formato de exibição foi um real (%g)
        if (strstr(texto, "%g") != NULL) {
            ultimo_foi_g = 1;
        } else if (strchr(texto, ';') != NULL || strchr(texto, '}') != NULL) {
            // Se finalizou um comando ou bloco, reseta o estado do %g
            ultimo_foi_g = 0;
        }
    }
}

int gerador_ultimo_foi_g() {
    int status = ultimo_foi_g;
    // Opcional: o reset já pode ser tratado na lógica de escrita para maior controle
    return status;
}

void gerador_fechar() {
    if (arquivo_saida) {
        fflush(arquivo_saida);
        fclose(arquivo_saida);
        arquivo_saida = NULL;
        #ifdef DEBUG
        printf("[DEBUG] Gerador: Arquivo fechado.\n");
        #endif
    }
}