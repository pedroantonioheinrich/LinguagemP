#include <stdio.h>
#include "logs.h"
#include "sintatico.h"

// Inicialização das variáveis globais que os módulos utilizam
int contador_unicidade = 0; 

int main(int argc, char *argv[]) {
    // 1. Validação de argumentos
    if (argc < 2) {
        P_LOG_ERRO("Uso: lp_compilador <arquivo.lp>");
        return 1;
    }

    // 2. Abertura do arquivo fonte
    FILE* f = fopen(argv[1], "r");
    if (!f) {
        P_LOG_HARDWARE("Nao foi possivel abrir o arquivo fonte.");
        return 1;
    }

    P_LOG_INFO("--- Iniciando Compilacao da Linguagem P (Modular) ---");
    
    // 3. Reset do estado para garantir compilação limpa
    contador_unicidade = 0; 

    // 4. Início da análise
    // O analisar(f) agora orquestra os tradutores específicos
    analisar(f);

    // 5. Finalização
    fclose(f);
    P_LOG_INFO("--- Processo concluido ---");
    
    return 0;
}