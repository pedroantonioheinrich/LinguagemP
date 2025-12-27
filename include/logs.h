/* * logs.h - Sistema de Diagnóstico da Linguagem P
 * Este arquivo define macros e funções para rastrear o comportamento da linguagem.
 */

#ifndef LOGS_H
#define LOGS_H

#include <stdio.h>
#include <time.h>

// Cores para Terminal (ANSI)
#define ANSI_COR_RESET   "\x1b[0m"
#define ANSI_COR_VERMELHO "\x1b[31m"
#define ANSI_COR_AMARELO  "\x1b[33m"
#define ANSI_COR_VERDE    "\x1b[32m"
#define ANSI_COR_CIANO    "\x1b[36m"
#define ANSI_COR_NEGrito  "\x1b[1m"

// Níveis de Log
typedef enum {
    LOG_INFO,     // Informações genéricas de fluxo
    LOG_AVISO,    // Funcionalidades ruins ou depreciadas
    LOG_ERRO,     // Erros que impedem a execução
    LOG_HARDWARE, // Rastro de acesso à memória/registradores
    LOG_DEBUG     // Rastro interno do compilador (sintático/léxico)
} NivelLog;

/*
 * Função para registrar eventos.
 * Adiciona automaticamente o timestamp, o nível do evento e cores no terminal.
 */
void registrar_log(NivelLog nivel, const char* mensagem, const char* arquivo, int linha);

/*
 * Macros para facilitar o uso e capturar automaticamente o arquivo e a linha do erro.
 */
#define P_LOG_INFO(msg)     registrar_log(LOG_INFO, msg, __FILE__, __LINE__)
#define P_LOG_AVISO(msg)    registrar_log(LOG_AVISO, msg, __FILE__, __LINE__)
#define P_LOG_ERRO(msg)     registrar_log(LOG_ERRO, msg, __FILE__, __LINE__)
#define P_LOG_HARDWARE(msg) registrar_log(LOG_HARDWARE, msg, __FILE__, __LINE__)

/*
 * Macro de Debug: Só imprime se a flag DEBUG estiver definida no compilador (ex: -DDEBUG)
 */
#ifdef DEBUG
    #define P_LOG_DEBUG(msg) registrar_log(LOG_DEBUG, msg, __FILE__, __LINE__)
#else
    #define P_LOG_DEBUG(msg) // Não faz nada em produção
#endif

#endif // LOGS_H