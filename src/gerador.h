#ifndef GERADOR_H
#define GERADOR_H

#include "lexico.h"

void gerador_abrir(const char* nome_arquivo);
void gerador_fechar();
void gerador_escrever(const char* codigo);
void gerador_traduzir_token(Token t);

#endif