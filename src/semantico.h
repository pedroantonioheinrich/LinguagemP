#ifndef SEMANTICO_H
#define SEMANTICO_H

#include "lexico.h"

typedef struct {
    char nome[100];
    TipoToken tipo;
    char tipo_registro[100];
    int eh_vetor;
    int nivel_escopo; // NOVO: 0 para global, 1+ para local
} Simbolo;

void semantico_adicionar(const char* nome, TipoToken tipo, int escopo);
void semantico_adicionar_com_tipo_reg(const char* nome, const char* tipo_reg, int escopo);
TipoToken semantico_obter_tipo(const char* nome);

void semantico_definir_registro(const char* nome);
void semantico_adicionar_campo_ao_reg(const char* nome_reg, const char* nome_campo, TipoToken tipo);
TipoToken semantico_obter_tipo_campo(const char* nome_var, const char* nome_campo);

void semantico_marcar_como_vetor(const char* nome);
int semantico_conferir_se_vetor(const char* nome);

// NOVO: Limpa as variáveis locais ao sair de uma função
void semantico_limpar_escopo_local();

#endif