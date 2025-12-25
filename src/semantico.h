#ifndef SEMANTICO_H
#define SEMANTICO_H

#include "lexico.h"

// A estrutura deve ficar apenas aqui para ser visível por todos os módulos
typedef struct {
    char nome[100];
    TipoToken tipo;
    int eh_constante;
    int eh_funcao;
    int num_parametros;
} Simbolo;

void semantico_adicionar(const char* nome, TipoToken tipo, int linha);
void semantico_adicionar_funcao(const char* nome, TipoToken tipo_retorno, int linha);
Simbolo* semantico_buscar(const char* nome);
int semantico_pode_atribuir(const char* nome);
int semantico_validar_chamada(const char* nome, int linha);
void semantico_marcar_constante(const char* nome);

#endif