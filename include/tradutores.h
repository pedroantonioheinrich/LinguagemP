#ifndef TRADUTORES_H
#define TRADUTORES_H

#include "lexico.h"

// --- FUNÇÕES DE SUPORTE (Definidas no sintatico.c) ---
void proximo();
void consumir(TipoToken tipo, const char* mensagem);
void bloco(); // Adicionado para permitir que tradutores chamem sub-blocos

// --- MODULO: FORMATADOR (formatador_c.c) ---
void formatador_finalizar_instrucao();
void formatador_quebrar_linha();
void formatador_indentar();

// --- MODULO: VARIAVEIS (tradutor_variavel.c) ---
void traduzir_declaracao_variavel();
void traduzir_acesso_identificador(const char* nome, int escopo_atual);

// --- MODULO: EXPRESSOES (tradutor_expressao.c) ---
void traduzir_expressao_ate(TipoToken limitador);
void traduzir_operador(TipoToken tipo);

// --- MODULO: STRINGS E E/S (tradutor_string.c) ---
void traduzir_comando_exibir();
void traduzir_literal_cadeia(const char* texto);

// --- MODULO: FLUXO (tradutor_fluxo.c) ---
void traduzir_inicio_se();
void traduzir_inicio_enquanto();
void traduzir_abrir_bloco();
void traduzir_fechar_bloco();

// --- MODULO: REGISTROS (tradutor_registro.c) ---
void traduzir_definicao_registro();
void traduzir_acesso_membro();

// --- MODULO: FUNCOES (tradutor_funcao.c) ---
void traduzir_declaracao_funcao();
void traduzir_comando_retorno();

#endif