#ifndef SEMANTICO_H
#define SEMANTICO_H

#include "lexico.h"

typedef struct {
    char nome[100];
    TipoToken tipo;
    int eh_constante;
} Simbolo;

void semantico_adicionar(const char* nome, TipoToken tipo, int linha);
void semantico_marcar_constante(const char* nome);
int semantico_pode_atribuir(const char* nome);
Simbolo* semantico_buscar(const char* nome); // A função que faltava

#endif