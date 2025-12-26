#include "logs.h"
#include <string.h> 
#include <time.h>
#include <stdio.h>

void registrar_log(NivelLog nivel, const char* mensagem, const char* arquivo, int linha) {
    time_t agora;
    time(&agora);
    char* data_hora = ctime(&agora);
    
    // Tratamento seguro da string de data/hora
    if (data_hora) {
        size_t len = strlen(data_hora);
        if (len > 0 && data_hora[len - 1] == '\n') {
            data_hora[len - 1] = '\0';
        }
    }

    const char* prefixo;
    const char* cor;

    // Mapeamento de níveis para prefixos e as cores definidas em logs.h
    switch (nivel) {
        case LOG_INFO:     
            prefixo = "[INFO]";     
            cor = ANSI_COR_VERDE; 
            break;
        case LOG_AVISO:    
            prefixo = "[AVISO]";    
            cor = ANSI_COR_AMARELO; 
            break;
        case LOG_ERRO:     
            prefixo = "[ERRO]";     
            cor = ANSI_COR_VERMELHO; 
            break;
        case LOG_HARDWARE: 
            prefixo = "[HARDWARE]"; 
            cor = ANSI_COR_NEGrito ANSI_COR_VERMELHO; 
            break;
        case LOG_DEBUG:    
            prefixo = "[DEBUG]";    
            cor = ANSI_COR_CIANO; 
            break;
        default:           
            prefixo = "[OUTRO]"; 
            cor = ANSI_COR_RESET;
    }

    // Impressão no console com cores
    printf("%s%s %s %s" ANSI_COR_RESET " (em %s:%d)\n", 
           cor, prefixo, data_hora ? data_hora : "", mensagem, arquivo, linha);

    // Gravação persistente no arquivo de log
    FILE* f = fopen("rastro_linguagem_p.log", "a");
    if (f) {
        fprintf(f, "%s %s %s (em %s:%d)\n", 
                data_hora ? data_hora : "N/A", prefixo, mensagem, arquivo, linha);
        fclose(f);
    }
}