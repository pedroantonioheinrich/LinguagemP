#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "semantico.h"
#include "logs.h"

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
    int escopo; // Armazena o ID único (contador_unicidade)
    int dimensoes; 
    int nivel_ponteiro; 
} Simbolo;

#define MAX_TABELA 5000
Simbolo tabela[MAX_TABELA];
int qtd_simbolos = 0;

Registro registros[100];
int qtd_registros = 0;

// --- FUNÇÕES DE GERENCIAMENTO DE SÍMBOLOS ---

void semantico_adicionar(const char* nome, TipoToken tipo, int escopo) {
    if (qtd_simbolos >= MAX_TABELA) {
        P_LOG_ERRO("Erro Semantico: Tabela de simbolos cheia!");
        return;
    }
    
    #ifdef DEBUG
    printf("[SEMANTIC-ADD] Registrando variavel '%s' com ID unico: %d\n", nome, escopo);
    #endif

    strcpy(tabela[qtd_simbolos].nome, nome);
    tabela[qtd_simbolos].tipo = tipo;
    tabela[qtd_simbolos].escopo = escopo; 
    tabela[qtd_simbolos].dimensoes = 0;
    tabela[qtd_simbolos].nivel_ponteiro = 0; 
    strcpy(tabela[qtd_simbolos].tipo_registro, "");
    qtd_simbolos++;
}

void semantico_adicionar_com_tipo_reg(const char* nome, const char* tipo_reg, int escopo) {
    if (qtd_simbolos >= MAX_TABELA) return;

    #ifdef DEBUG
    printf("[SEMANTIC-ADD-REG] Registrando instancia de registro '%s %s' com ID: %d\n", tipo_reg, nome, escopo);
    #endif

    strcpy(tabela[qtd_simbolos].nome, nome);
    tabela[qtd_simbolos].tipo = TOKEN_REGISTRO;
    tabela[qtd_simbolos].escopo = escopo;
    tabela[qtd_simbolos].dimensoes = 0;
    tabela[qtd_simbolos].nivel_ponteiro = 0;
    strcpy(tabela[qtd_simbolos].tipo_registro, tipo_reg);
    qtd_simbolos++;
}

int semantico_obter_escopo(const char* nome, int escopo_atual) {
    (void)escopo_atual; 
    // Busca do mais recente para o mais antigo (pilha de simbolos)
    for (int i = qtd_simbolos - 1; i >= 0; i--) {
        if (strcmp(tabela[i].nome, nome) == 0) {
            return tabela[i].escopo;
        }
    }
    return -1; 
}

void semantico_marcar_ponteiro(const char* nome) {
    for (int i = qtd_simbolos - 1; i >= 0; i--) {
        if (strcmp(tabela[i].nome, nome) == 0) {
            tabela[i].nivel_ponteiro++; 
            #ifdef DEBUG
            printf("[SEMANTIC-PTR] Variavel '%s' marcada como ponteiro (Nivel: %d)\n", nome, tabela[i].nivel_ponteiro);
            #endif
            return;
        }
    }
}

int semantico_eh_ponteiro(const char* nome) {
    for (int i = qtd_simbolos - 1; i >= 0; i--) {
        if (strcmp(tabela[i].nome, nome) == 0) {
            return (tabela[i].nivel_ponteiro > 0);
        }
    }
    return 0;
}

int semantico_obter_nivel_ponteiro(const char* nome) {
    for (int i = qtd_simbolos - 1; i >= 0; i--) {
        if (strcmp(tabela[i].nome, nome) == 0) return tabela[i].nivel_ponteiro;
    }
    return 0;
}

void semantico_marcar_matriz(const char* nome, int dimensoes) {
    for (int i = qtd_simbolos - 1; i >= 0; i--) {
        if (strcmp(tabela[i].nome, nome) == 0) {
            tabela[i].dimensoes = dimensoes;
            #ifdef DEBUG
            printf("[SEMANTIC-ARRAY] Variavel '%s' marcada com %d dimensoes\n", nome, dimensoes);
            #endif
            return;
        }
    }
}

int semantico_obter_dimensoes(const char* nome) {
    for (int i = qtd_simbolos - 1; i >= 0; i--) {
        if (strcmp(tabela[i].nome, nome) == 0) {
            return tabela[i].dimensoes;
        }
    }
    return 0;
}

int semantico_eh_matriz(const char* nome) {
    return semantico_obter_dimensoes(nome) > 0;
}

TipoToken semantico_obter_tipo(const char* nome) {
    for (int i = qtd_simbolos - 1; i >= 0; i--) {
        if (strcmp(tabela[i].nome, nome) == 0) return tabela[i].tipo;
    }
    return TOKEN_ERRO;
}

// --- GERENCIAMENTO DE REGISTROS (STRUCTS) ---

void semantico_definir_registro(const char* nome) {
    if (qtd_registros >= 100) return;
    for(int i=0; i < qtd_registros; i++) {
        if(strcmp(registros[i].nome, nome) == 0) return;
    }

    #ifdef DEBUG
    printf("[SEMANTIC-DEF-REG] Definindo nova estrutura de registro: %s\n", nome);
    #endif

    strcpy(registros[qtd_registros].nome, nome);
    registros[qtd_registros].qtd_campos = 0;
    qtd_registros++;
}

int semantico_existe_registro(const char* nome) {
    for (int i = 0; i < qtd_registros; i++) {
        if (strcmp(registros[i].nome, nome) == 0) return 1;
    }
    return 0;
}

void semantico_adicionar_campo_ao_reg(const char* nome_reg, const char* nome_campo, TipoToken tipo) {
    for (int i = 0; i < qtd_registros; i++) {
        if (strcmp(registros[i].nome, nome_reg) == 0) {
            if (registros[i].qtd_campos < 20) {
                int pos = registros[i].qtd_campos;
                strcpy(registros[i].campos[pos].nome, nome_campo);
                registros[i].campos[pos].tipo = tipo;
                registros[i].qtd_campos++;
                #ifdef DEBUG
                printf("[SEMANTIC-FIELD] Campo '%s' adicionado ao registro '%s'\n", nome_campo, nome_reg);
                #endif
            }
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
    if (strlen(tipo_reg) == 0) return TOKEN_ERRO;
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

void semantico_limpar_escopo(int escopo) {
    (void)escopo;
    #ifdef DEBUG
    printf("[SEMANTIC-CLEAN] Solicitada limpeza de escopo (Não implementada para manter IDs unicos globais)\n");
    #endif
}