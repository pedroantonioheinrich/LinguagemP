#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "semantico.h"

typedef struct {
    char nome[100];
    TipoToken tipo;
} Campo;

typedef struct {
    char nome[100];
    Campo campos[20];
    int qtd_campos;
} Registro;

typedef struct {
    char nome[100];
    TipoToken tipo;
    char tipo_registro[100];
    int escopo;
    int eh_vetor;
} Simbolo;

Simbolo tabela[100];
int qtd_simbolos = 0;

Registro registros[20];
int qtd_registros = 0;

void semantico_adicionar(const char* nome, TipoToken tipo, int escopo) {
    strcpy(tabela[qtd_simbolos].nome, nome);
    tabela[qtd_simbolos].tipo = tipo;
    tabela[qtd_simbolos].escopo = escopo;
    tabela[qtd_simbolos].eh_vetor = 0;
    strcpy(tabela[qtd_simbolos].tipo_registro, "");
    qtd_simbolos++;
}

void semantico_adicionar_com_tipo_reg(const char* nome, const char* tipo_reg, int escopo) {
    strcpy(tabela[qtd_simbolos].nome, nome);
    tabela[qtd_simbolos].tipo = TOKEN_REGISTRO;
    tabela[qtd_simbolos].escopo = escopo;
    tabela[qtd_simbolos].eh_vetor = 0;
    strcpy(tabela[qtd_simbolos].tipo_registro, tipo_reg);
    qtd_simbolos++;
}

void semantico_marcar_como_vetor(const char* nome) {
    for (int i = 0; i < qtd_simbolos; i++) {
        if (strcmp(tabela[i].nome, nome) == 0) {
            tabela[i].eh_vetor = 1;
            return;
        }
    }
}

TipoToken semantico_obter_tipo(const char* nome) {
    for (int i = qtd_simbolos - 1; i >= 0; i--) {
        if (strcmp(tabela[i].nome, nome) == 0) return tabela[i].tipo;
    }
    return TOKEN_ERRO;
}

void semantico_definir_registro(const char* nome) {
    strcpy(registros[qtd_registros].nome, nome);
    registros[qtd_registros].qtd_campos = 0;
    qtd_registros++;
}

// Implementação da função que faltava:
int semantico_existe_registro(const char* nome) {
    for (int i = 0; i < qtd_registros; i++) {
        if (strcmp(registros[i].nome, nome) == 0) return 1;
    }
    return 0;
}

void semantico_adicionar_campo_ao_reg(const char* nome_reg, const char* nome_campo, TipoToken tipo) {
    for (int i = 0; i < qtd_registros; i++) {
        if (strcmp(registros[i].nome, nome_reg) == 0) {
            int pos = registros[i].qtd_campos;
            strcpy(registros[i].campos[pos].nome, nome_campo);
            registros[i].campos[pos].tipo = tipo;
            registros[i].qtd_campos++;
            return;
        }
    }
}

TipoToken semantico_obter_tipo_campo(const char* nome_var, const char* nome_campo) {
    char tipo_reg[100] = "";
    for (int i = qtd_simbolos - 1; i >= 0; i--) {
        if (strcmp(tabela[i].nome, nome_var) == 0) {
            strcpy(tipo_reg, tabela[i].tipo_registro);
            break;
        }
    }
    for (int i = 0; i < qtd_registros; i++) {
        if (strcmp(registros[i].nome, tipo_reg) == 0) {
            for (int j = 0; j < registros[i].qtd_campos; j++) {
                if (strcmp(registros[i].campos[j].nome, nome_campo) == 0)
                    return registros[i].campos[j].tipo;
            }
        }
    }
    return TOKEN_ERRO;
}

void semantico_limpar_escopo_local() {
    int i = 0;
    while (i < qtd_simbolos) {
        if (tabela[i].escopo == 1) {
            for (int j = i; j < qtd_simbolos - 1; j++) tabela[j] = tabela[j+1];
            qtd_simbolos--;
        } else i++;
    }
}