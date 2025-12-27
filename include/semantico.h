#ifndef SEMANTICO_H
#define SEMANTICO_H

#include "lexico.h"

// --- Gerenciamento de Variáveis e Escopo ---
void semantico_adicionar(const char* nome, TipoToken tipo, int escopo);
void semantico_adicionar_com_tipo_reg(const char* nome, const char* tipo_reg, int escopo);

/**
 * Define o número de dimensões para arrays (1 para vetor, 2 para matriz, etc)
 */
void semantico_marcar_matriz(const char* nome, int dimensoes);
int semantico_obter_dimensoes(const char* nome);

TipoToken semantico_obter_tipo(const char* nome);
void semantico_limpar_escopo(int escopo); 

/**
 * Necessário para resolver o Shadowing no tradutor C.
 * Retorna o ID único (escopo) da versão mais recente da variável.
 */
int semantico_obter_escopo(const char* nome, int escopo_atual);

// --- Suporte a Ponteiros e Açúcar Sintático ---
void semantico_marcar_ponteiro(const char* nome);
int semantico_eh_ponteiro(const char* nome);

/**
 * Retorna o nível de indireção (ex: 1 para *, 2 para **).
 * Útil para o sintático decidir entre usar '.' ou '->'.
 */
int semantico_obter_nivel_ponteiro(const char* nome);

// --- Gerenciamento de Registros (Structs) ---
void semantico_definir_registro(const char* nome);
int semantico_existe_registro(const char* nome);
void semantico_adicionar_campo_ao_reg(const char* nome_reg, const char* nome_campo, TipoToken tipo);
TipoToken semantico_obter_tipo_campo(const char* nome_var, const char* nome_campo);

#endif