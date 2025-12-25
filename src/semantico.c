#include <string.h>
#include <stdio.h>
#include "semantico.h"

Simbolo tabela[100];
int total_simbolos = 0;

void semantico_adicionar(const char* nome, TipoToken tipo, int linha) {
    for (int i = 0; i < total_simbolos; i++) {
        if (strcmp(tabela[i].nome, nome) == 0) {
            printf("Erro Semantico na linha %d: Variavel '%s' ja declarada.\n", linha, nome);
            return;
        }
    }
    strcpy(tabela[total_simbolos].nome, nome);
    tabela[total_simbolos].tipo = tipo;
    tabela[total_simbolos].eh_constante = 0;
    total_simbolos++;
}

Simbolo* semantico_buscar(const char* nome) {
    for (int i = 0; i < total_simbolos; i++) {
        if (strcmp(tabela[i].nome, nome) == 0) return &tabela[i];
    }
    return NULL;
}

void semantico_marcar_constante(const char* nome) {
    Simbolo* s = semantico_buscar(nome);
    if (s) s->eh_constante = 1;
}

int semantico_pode_atribuir(const char* nome) {
    Simbolo* s = semantico_buscar(nome);
    if (s && s->eh_constante) return 0;
    return 1;
}