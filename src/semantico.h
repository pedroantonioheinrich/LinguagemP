#ifndef SEMANTICO_H
#define SEMANTICO_H

#include "lexico.h"

void semantico_adicionar(const char* nome, TipoToken tipo, int escopo);
void semantico_adicionar_com_tipo_reg(const char* nome, const char* tipo_reg, int escopo);
TipoToken semantico_obter_tipo(const char* nome);
void semantico_limpar_escopo_local();

void semantico_definir_registro(const char* nome);
void semantico_adicionar_campo_ao_reg(const char* nome_reg, const char* nome_campo, TipoToken tipo);
TipoToken semantico_obter_tipo_campo(const char* nome_var, const char* nome_campo);
void semantico_marcar_como_vetor(const char* nome);

// Nova função necessária:
int semantico_existe_registro(const char* nome);

#endif