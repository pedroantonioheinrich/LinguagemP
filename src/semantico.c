#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "semantico.h"
#include "logs.h"

#define MAX_SIMBOLOS 200

Simbolo tabela[MAX_SIMBOLOS];
int total_simbolos = 0;

void semantico_adicionar(const char* nome, TipoToken tipo, int linha) {
    for (int i = 0; i < total_simbolos; i++) {
        if (strcmp(tabela[i].nome, nome) == 0) {
            char erro[256];
            snprintf(erro, sizeof(erro), "Erro Semantico na linha %d: Identificador '%s' ja declarado.", linha, nome);
            P_LOG_ERRO(erro); return;
        }
    }
    strcpy(tabela[total_simbolos].nome, nome);
    tabela[total_simbolos].tipo = tipo;
    tabela[total_simbolos].eh_constante = 0;
    tabela[total_simbolos].eh_funcao = 0;
    tabela[total_simbolos].num_parametros = 0;
    total_simbolos++;
}

void semantico_adicionar_funcao(const char* nome, TipoToken tipo_retorno, int n_params, int linha) {
    semantico_adicionar(nome, tipo_retorno, linha);
    tabela[total_simbolos - 1].eh_funcao = 1;
    tabela[total_simbolos - 1].num_parametros = n_params;
}

Simbolo* semantico_buscar(const char* nome) {
    for (int i = 0; i < total_simbolos; i++) {
        if (strcmp(tabela[i].nome, nome) == 0) return &tabela[i];
    }
    return NULL;
}

int semantico_validar_chamada(const char* nome, int n_params_passados, int linha) {
    Simbolo* s = semantico_buscar(nome);
    if (!s || !s->eh_funcao) {
        char erro[256];
        snprintf(erro, sizeof(erro), "Erro Semantico na linha %d: Funcao '%s' nao declarada.", linha, nome);
        P_LOG_ERRO(erro); exit(1);
    }
    if (s->num_parametros != n_params_passados) {
        char erro[256];
        snprintf(erro, sizeof(erro), "Erro Semantico na linha %d: Funcao '%s' espera %d parametros (recebeu %d).", linha, nome, s->num_parametros, n_params_passados);
        P_LOG_ERRO(erro); exit(1);
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