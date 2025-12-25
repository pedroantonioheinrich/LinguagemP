#ifndef SEMANTICO_H
#define SEMANTICO_H

#include "lexico.h"

typedef struct {
    char nome[100];
    TipoToken tipo;
    int eh_constante;
    int eh_funcao;
    int num_parametros; // Novo campo
} Simbolo;

void semantico_adicionar(const char* nome, TipoToken tipo, int linha);
void semantico_adicionar_funcao(const char* nome, TipoToken tipo_retorno, int n_params, int linha);
Simbolo* semantico_buscar(const char* nome);
int semantico_pode_atribuir(const char* nome);
int semantico_validar_chamada(const char* nome, int n_params_passados, int linha);
void semantico_marcar_constante(const char* nome);

#endif