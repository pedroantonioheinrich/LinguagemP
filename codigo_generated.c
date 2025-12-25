#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

void piscar(double pino, double tempo) {
    printf("[HARDWARE] Pino %d: LIGADO\n", (int)pino);
    ;
    usleep(tempo * 1000);
    ;
    printf("[HARDWARE] Pino %d: DESLIGADO\n", (int)pino);
    ;
    usleep(tempo * 1000);
    ;
    }


int main()  {
    int LED = 13;
    printf("%s\n", "Iniciando sequencia de pisca...");
    ;
    piscar(LED, 200);
    ;
    piscar(LED, 200);
    ;
    printf("%s\n", "Sequencia concluida.");
    ;
    return 0;
    }

