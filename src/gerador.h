#ifndef GERADOR_H
#define GERADOR_H

/**
 * Abre o arquivo de saída para a geração do código C traduzido.
 */
void gerador_abrir(const char* nome_arquivo);

/**
 * Escreve uma string diretamente no arquivo de saída.
 * Realiza o flush imediato para garantir integridade em caso de erro no compilador.
 */
void gerador_escrever(const char* texto);

/**
 * Fecha o arquivo de saída e limpa os buffers.
 */
void gerador_fechar();

/**
 * Retorna se o último formato de exibição gerado foi um número real (%g).
 * Utilizado para controle interno da função exibir().
 */
int gerador_ultimo_foi_g();

#endif