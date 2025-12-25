/* * logs.h - Sistema de Diagnóstico da Linguagem P
 * Este arquivo define macros e funções para rastrear o comportamento da linguagem.
 */

#ifndef LOGS_H
#define LOGS_H

#include <stdio.h>
#include <time.h>

// Níveis de Log
typedef enum {
    LOG_INFO,     // Informações genéricas de fluxo
    LOG_AVISO,    // Funcionalidades ruins ou depreciadas
    LOG_ERRO,     // Erros que impedem a execução
    LOG_HARDWARE  // Rastro de acesso à memória/registradores
} NivelLog;

/*
 * Função para registrar eventos.
 * Adiciona automaticamente o timestamp e o nível do evento.
 */
void registrar_log(NivelLog nivel, const char* mensagem, const char* arquivo, int linha);

/*
 * Macros para facilitar o uso e capturar automaticamente o arquivo e a linha do erro.
 */
#define P_LOG_INFO(msg)     registrar_log(LOG_INFO, msg, __FILE__, __LINE__)
#define P_LOG_AVISO(msg)    registrar_log(LOG_AVISO, msg, __FILE__, __LINE__)
#define P_LOG_ERRO(msg)     registrar_log(LOG_ERRO, msg, __FILE__, __LINE__)
#define P_LOG_HARDWARE(msg) registrar_log(LOG_HARDWARE, msg, __FILE__, __LINE__)

#endif // LOGS_H