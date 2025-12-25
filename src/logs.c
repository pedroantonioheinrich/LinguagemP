#include "logs.h"
#include <string.h> 
#include <time.h>


// Cores para o console
#define COR_VERMELHO "\033[0;31m"
#define COR_AMARELO  "\033[0;33m"
#define COR_VERDE    "\033[0;32m"
#define COR_RESET    "\033[0m"

void registrar_log(NivelLog nivel, const char* mensagem, const char* arquivo, int linha) {
    time_t agora;
    time(&agora);
    char* data_hora = ctime(&agora);
    if (data_hora) {
        data_hora[strlen(data_hora) - 1] = '\0'; // Agora o strlen vai funcionar!
    }

    const char* prefixo;
    const char* cor;

    switch (nivel) {
        case LOG_INFO:     prefixo = "[INFO]";     cor = COR_VERDE; break;
        case LOG_AVISO:    prefixo = "[AVISO]";    cor = COR_AMARELO; break;
        case LOG_ERRO:     prefixo = "[ERRO]";     cor = COR_VERMELHO; break;
        case LOG_HARDWARE: prefixo = "[HARDWARE]"; cor = COR_VERMELHO; break;
        default:           prefixo = "[DESCONHECIDO]"; cor = COR_RESET;
    }

    printf("%s %s %s (em %s:%d)%s\n", cor, prefixo, mensagem, arquivo, linha, COR_RESET);

    FILE* f = fopen("rastro_linguagem_p.log", "a");
    if (f) {
        fprintf(f, "%s %s %s (em %s:%d)\n", data_hora ? data_hora : "N/A", prefixo, mensagem, arquivo, linha);
        fclose(f);
    }
}