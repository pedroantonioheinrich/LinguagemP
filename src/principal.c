#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sintatico.h"

/**
 * Exibe as instruções de uso do compilador
 */
void mostrar_ajuda() {
    printf("================================================\n");
    printf("        COMPILADOR DA LINGUAGEM P               \n");
    printf("================================================\n");
    printf("Uso: lp [opcao] <arquivo.lp>\n\n");
    printf("Opcoes:\n");
    printf("  -c    Apenas traduz para 'codigo_gerado.c'\n");
    printf("  -r    Traduz, compila e executa imediatamente\n");
    printf("  -h    Mostra esta tela de ajuda\n");
    printf("================================================\n");
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        mostrar_ajuda();
        return 1;
    }

    char* arquivo_entrada = NULL;
    int modo_execucao = 0; // 0 = apenas traduz, 1 = executa (-r)

    // Lógica de argumentos
    if (argc == 2) {
        if (strcmp(argv[1], "-h") == 0) {
            mostrar_ajuda();
            return 0;
        }
        arquivo_entrada = argv[1];
    } 
    else if (argc == 3) {
        if (strcmp(argv[1], "-r") == 0) {
            modo_execucao = 1;
            arquivo_entrada = argv[2];
        } else if (strcmp(argv[1], "-c") == 0) {
            modo_execucao = 0;
            arquivo_entrada = argv[2];
        } else {
            arquivo_entrada = argv[2];
        }
    }

    if (arquivo_entrada == NULL) {
        mostrar_ajuda();
        return 1;
    }

    // Tentar abrir o arquivo fonte
    FILE* f = fopen(arquivo_entrada, "r");
    if (!f) {
        fprintf(stderr, "Erro: Nao foi possivel abrir o arquivo '%s'\n", arquivo_entrada);
        return 1;
    }

    printf("Iniciando traducao de: %s\n", arquivo_entrada);
    
    // Chama o analisador sintatico (que inicia o processo)
    analisar(f);
    fclose(f);

    // Se o modo for execução direta (-r)
    if (modo_execucao) {
        printf("Traducao concluida. Compilando e executando...\n");
        printf("------------------------------------------------\n");

        int status;

        #ifdef _WIN32
            // Lógica para Windows
            // Compila o C gerado em um executavel temporario e roda
            status = system("gcc codigo_gerado.c -o temp_exec.exe && temp_exec.exe");
            
            // Limpa os arquivos temporarios no Windows
            system("del temp_exec.exe codigo_gerado.c");
        #else
            // Lógica para Linux e macOS
            // Compila o C gerado em um executavel temporario e roda
            status = system("gcc codigo_gerado.c -o temp_exec && ./temp_exec");
            
            // Limpa os arquivos temporarios no Unix
            system("rm temp_exec codigo_gerado.c");
        #endif

        printf("\n------------------------------------------------\n");
        if (status != 0) {
            printf("Aviso: O programa encerrou com código de erro %d.\n", status);
        } else {
            printf("Execucao finalizada com sucesso.\n");
        }
    } else {
        printf("Sucesso! O arquivo 'codigo_gerado.c' foi criado.\n");
        printf("Para compilar manualmente use: gcc codigo_gerado.c -o programa\n");
    }

    return 0;
}