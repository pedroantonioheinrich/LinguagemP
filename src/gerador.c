#include <stdio.h>
#include <string.h>
#include <stdarg.h>
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
        fflush(arquivo_saida);

        // Verifica se o último formato de exibição foi um real (%g)
        // Isso ajuda os tradutores a saberem se precisam tratar vírgula/ponto
        if (strstr(texto, "%g") != NULL) {
            ultimo_foi_g = 1;
        } else if (strchr(texto, ';') != NULL || strchr(texto, '}') != NULL) {
            // Se finalizou um comando ou bloco, reseta o estado do %g
            ultimo_foi_g = 0;
        }
    }
}

/**
 * Nova função para suportar escritas formatadas (estilo printf)
 * Útil para declarações de vetores e tipos complexos.
 */
void gerador_escrever_formatado(const char* formato, ...) {
    if (arquivo_saida && formato) {
        va_list args;
        va_start(args, formato);
        
        // Escrita formatada direto no arquivo
        vfprintf(arquivo_saida, formato, args);
        
        va_end(args);
        fflush(arquivo_saida);
    }
}

int gerador_ultimo_foi_g() {
    return ultimo_foi_g;
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