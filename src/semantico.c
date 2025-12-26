#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "semantico.h"
#include "logs.h"

// Tabela de Símbolos Principal
Simbolo tabela[500];
int simbolos_count = 0;

// Estruturas para Gerenciamento de Registros (Structs)
typedef struct {
    char nome[100];
    Simbolo campos[20];
    int campos_count;
} RegistroDef;

RegistroDef registros[50];
int registros_count = 0;

/**
 * Adiciona um novo símbolo à tabela.
 * escopo: 0 para Global, 1+ para Local.
 */
void semantico_adicionar(const char* nome, TipoToken tipo, int escopo) {
    // Verifica se a variável já existe NO MESMO ESCOPO
    // Isso permite "Shadowing" (variável local com mesmo nome da global)
    for(int i = 0; i < simbolos_count; i++) {
        if(strcmp(tabela[i].nome, nome) == 0 && tabela[i].nivel_escopo == escopo) {
            char msg[200];
            snprintf(msg, 200, "Erro Semantico: Variavel '%s' ja declarada neste escopo.", nome);
            P_LOG_ERRO(msg); 
            exit(1);
        }
    }
    
    if (simbolos_count >= 500) {
        P_LOG_ERRO("Erro Semantico: Tabela de simbolos cheia.");
        exit(1);
    }

    strcpy(tabela[simbolos_count].nome, nome);
    tabela[simbolos_count].tipo = tipo;
    tabela[simbolos_count].eh_vetor = 0;
    tabela[simbolos_count].nivel_escopo = escopo;
    tabela[simbolos_count].tipo_registro[0] = '\0';
    simbolos_count++;
}

/**
 * Remove todos os símbolos que pertencem ao escopo local (nivel > 0).
 * Chamada sempre ao final da análise de uma função ou do bloco inicio.
 */
void semantico_limpar_escopo_local() {
    int nova_contagem = 0;
    for (int i = 0; i < simbolos_count; i++) {
        if (tabela[i].nivel_escopo == 0) {
            // Mantém apenas o que for Global
            tabela[nova_contagem] = tabela[i];
            nova_contagem++;
        }
    }
    simbolos_count = nova_contagem;
}

/**
 * Define um novo tipo de Registro (Struct).
 */
void semantico_definir_registro(const char* nome) {
    for(int i = 0; i < registros_count; i++) {
        if(strcmp(registros[i].nome, nome) == 0) {
            P_LOG_ERRO("Erro Semantico: Registro ja definido.");
            exit(1);
        }
    }
    strcpy(registros[registros_count].nome, nome);
    registros[registros_count].campos_count = 0;
    registros_count++;
}

/**
 * Adiciona um campo interno a um registro já definido.
 */
void semantico_adicionar_campo_ao_reg(const char* nome_reg, const char* nome_campo, TipoToken tipo) {
    for(int i = 0; i < registros_count; i++) {
        if(strcmp(registros[i].nome, nome_reg) == 0) {
            int c = registros[i].campos_count;
            strcpy(registros[i].campos[c].nome, nome_campo);
            registros[i].campos[c].tipo = tipo;
            registros[i].campos_count++;
            return;
        }
    }
}

/**
 * Busca o tipo de uma variável. 
 * IMPORTANTE: Percorre de trás para frente para priorizar o escopo local.
 */
TipoToken semantico_obter_tipo(const char* nome) {
    for(int i = simbolos_count - 1; i >= 0; i--) {
        if(strcmp(tabela[i].nome, nome) == 0) {
            return tabela[i].tipo;
        }
    }
    return TOKEN_ERRO;
}

/**
 * Marca uma variável como sendo um vetor.
 */
void semantico_marcar_como_vetor(const char* nome) {
    for(int i = simbolos_count - 1; i >= 0; i--) {
        if(strcmp(tabela[i].nome, nome) == 0) {
            tabela[i].eh_vetor = 1;
            return;
        }
    }
}

/**
 * Verifica se o identificador é um vetor.
 */
int semantico_conferir_se_vetor(const char* nome) {
    for(int i = simbolos_count - 1; i >= 0; i--) {
        if(strcmp(tabela[i].nome, nome) == 0) {
            return tabela[i].eh_vetor;
        }
    }
    return 0;
}

/**
 * Adiciona uma variável que é do tipo Registro.
 */
void semantico_adicionar_com_tipo_reg(const char* nome, const char* tipo_reg, int escopo) {
    semantico_adicionar(nome, TOKEN_REGISTRO, escopo);
    strcpy(tabela[simbolos_count - 1].tipo_registro, tipo_reg);
}

/**
 * Obtém o tipo de um campo específico dentro de uma variável do tipo registro.
 */
TipoToken semantico_obter_tipo_campo(const char* nome_var, const char* nome_campo) {
    char tipo_reg[100] = "";
    
    // 1. Encontra qual é o tipo de registro da variável
    for(int i = simbolos_count - 1; i >= 0; i--) {
        if(strcmp(tabela[i].nome, nome_var) == 0) {
            strcpy(tipo_reg, tabela[i].tipo_registro);
            break;
        }
    }

    // 2. Busca o campo na definição daquele registro
    for(int i = 0; i < registros_count; i++) {
        if(strcmp(registros[i].nome, tipo_reg) == 0) {
            for(int j = 0; j < registros[i].campos_count; j++) {
                if(strcmp(registros[i].campos[j].nome, nome_campo) == 0) {
                    return registros[i].campos[j].tipo;
                }
            }
        }
    }
    return TOKEN_ERRO;
}