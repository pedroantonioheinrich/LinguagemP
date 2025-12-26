#ifndef GERADOR_H
#define GERADOR_H

void gerador_abrir(const char* nome_arquivo);
void gerador_escrever(const char* texto);
void gerador_fechar();
int gerador_ultimo_foi_g(); // Adicionado para eliminar o warning

#endif