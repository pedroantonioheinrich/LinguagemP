#include "../src/logs.h"
#include <stdio.h>
#include <string.h>

int main() {
    printf("=== INICIANDO TESTES DE RESILIENCIA DA LINGUAGEM P ===\n\n");

    // Teste 1: Log de Informação
    P_LOG_INFO("Teste de informacao: O sistema de rastro iniciou.");

    // Teste 2: Funcionalidade Ruim (Aviso)
    P_LOG_AVISO("Teste de funcionalidade ruim: Tentativa de usar extensao incorreta.");

    // Teste 3: Erro Crítico
    P_LOG_ERRO("Teste de erro: Falha simulada para validar captura.");

    // Teste 4: Hardware (Onde a Linguagem P vai brilhar)
    P_LOG_HARDWARE("Teste de Hardware: Simulando acesso direto ao endereco 0x00FF.");

    // Validação do arquivo físico
    FILE *f = fopen("rastro_linguagem_p.log", "r");
    if (f) {
        printf("\n[SUCESSO] O arquivo 'rastro_linguagem_p.log' foi gerado corretamente.\n");
        fclose(f);
    } else {
        printf("\n[FALHA] O sistema nao conseguiu criar o arquivo de log físico.\n");
        return 1;
    }

    printf("\n=== TESTES CONCLUIDOS COM SUCESSO ===\n");
    return 0;
}