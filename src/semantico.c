#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantico.h"
#include "logs.h"

Simbolo tabela[1000];
int total_simbolos = 0;

void semantico_adicionar(const char* nome, TipoToken tipo, int linha) {
    for(int i = 0; i < total_simbolos; i++) {
        if(strcmp(tabela[i].nome, nome) == 0) {
            char erro[256];
            snprintf(erro, 256, "Erro Semantico na linha %d: Variavel '%s' ja declarada.", linha, nome);
            P_LOG_ERRO(erro); exit(1);
        }
    }
    strncpy(tabela[total_simbolos].nome, nome, 99);
    tabela[total_simbolos].tipo = tipo;
    tabela[total_simbolos].eh_constante = 0;
    total_simbolos++;
}

void semantico_marcar_constante(const char* nome) {
    for(int i = 0; i < total_simbolos; i++) {
        if(strcmp(tabela[i].nome, nome) == 0) {
            tabela[i].eh_constante = 1;
            return;
        }
    }
}

int semantico_existe(const char* nome) {
    for(int i = 0; i < total_simbolos; i++) {
        if(strcmp(tabela[i].nome, nome) == 0) return 1;
    }
    return 0;
}

int semantico_pode_atribuir(const char* nome) {
    for(int i = 0; i < total_simbolos; i++) {
        if(strcmp(tabela[i].nome, nome) == 0) return !tabela[i].eh_constante;
    }
    return 1;
}

TipoToken semantico_get_tipo(const char* nome) {
    for(int i = 0; i < total_simbolos; i++) {
        if(strcmp(tabela[i].nome, nome) == 0) return tabela[i].tipo;
    }
    return TOKEN_ERRO;
}