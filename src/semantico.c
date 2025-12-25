#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "semantico.h"
#include "logs.h"

#define MAX_SIMBOLOS 200

// Removida a definição da struct Simbolo daqui, pois já vem do semantico.h
Simbolo tabela[MAX_SIMBOLOS];
int total_simbolos = 0;

void semantico_adicionar(const char* nome, TipoToken tipo, int linha) {
    for (int i = 0; i < total_simbolos; i++) {
        if (strcmp(tabela[i].nome, nome) == 0) {
            char erro[256];
            snprintf(erro, sizeof(erro), "Erro Semantico na linha %d: O identificador '%s' ja foi declarado.", linha, nome);
            P_LOG_ERRO(erro);
            return;
        }
    }

    if (total_simbolos >= MAX_SIMBOLOS) {
        P_LOG_ERRO("Erro Semantico: Tabela de simbolos cheia.");
        exit(1);
    }

    strcpy(tabela[total_simbolos].nome, nome);
    tabela[total_simbolos].tipo = tipo;
    tabela[total_simbolos].eh_constante = 0;
    tabela[total_simbolos].eh_funcao = 0;
    tabela[total_simbolos].num_parametros = 0;
    total_simbolos++;
}

void semantico_adicionar_funcao(const char* nome, TipoToken tipo_retorno, int linha) {
    semantico_adicionar(nome, tipo_retorno, linha);
    tabela[total_simbolos - 1].eh_funcao = 1;
}

Simbolo* semantico_buscar(const char* nome) {
    for (int i = 0; i < total_simbolos; i++) {
        if (strcmp(tabela[i].nome, nome) == 0) {
            return &tabela[i];
        }
    }
    return NULL;
}

int semantico_validar_chamada(const char* nome, int linha) {
    Simbolo* s = semantico_buscar(nome);
    if (s == NULL) {
        char erro[256];
        snprintf(erro, sizeof(erro), "Erro Semantico na linha %d: Funcao '%s' nao foi declarada.", linha, nome);
        P_LOG_ERRO(erro);
        exit(1); // Interrompe para não gerar código C inválido
    }
    if (!s->eh_funcao) {
        char erro[256];
        snprintf(erro, sizeof(erro), "Erro Semantico na linha %d: '%s' e uma variavel, nao uma funcao.", linha, nome);
        P_LOG_ERRO(erro);
        exit(1);
    }
    return 1;
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