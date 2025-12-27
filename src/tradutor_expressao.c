#include <stdio.h>
#include <string.h>
#include "tradutores.h"
#include "lexico.h"
#include "gerador.h"

extern Token token_atual;

void traduzir_operador(TipoToken tipo) {
    switch (tipo) {
        case TOKEN_MAIS:          gerador_escrever(" + "); break;
        case TOKEN_MENOS:         gerador_escrever(" - "); break;
        case TOKEN_ASTERISCO:     gerador_escrever(" * "); break;
        case TOKEN_BARRA:         gerador_escrever(" / "); break;
        case TOKEN_PERCENTUAL:    gerador_escrever(" % "); break; 
        case TOKEN_IGUAL_IGUAL:   gerador_escrever(" == "); break;
        case TOKEN_DIFERENTE:     gerador_escrever(" != "); break;
        case TOKEN_MENOR:         gerador_escrever(" < "); break;
        case TOKEN_MAIOR:         gerador_escrever(" > "); break;
        case TOKEN_MENOR_IGUAL:   gerador_escrever(" <= "); break;
        case TOKEN_MAIOR_IGUAL:   gerador_escrever(" >= "); break;
        case TOKEN_E_LOGICO:      gerador_escrever(" && "); break;
        case TOKEN_OU_LOGICO:     gerador_escrever(" || "); break;
        case TOKEN_NAO_LOGICO:    gerador_escrever("!"); break;
        case TOKEN_ATRIBUICAO:    gerador_escrever(" = "); break;
        case TOKEN_SETA:          gerador_escrever("->"); break;
        case TOKEN_PONTO:         gerador_escrever("."); break;
        case TOKEN_MAIS_MAIS:     gerador_escrever("++"); break;
        case TOKEN_MENOS_MENOS:   gerador_escrever("--"); break; 
        default: break;
    }
}

void traduzir_expressao_ate(TipoToken limitador) {
    while (token_atual.tipo != limitador && 
           token_atual.tipo != TOKEN_EOF && 
           token_atual.tipo != TOKEN_ATE &&
           token_atual.tipo != TOKEN_PONTO_VIRGULA) {
        
        if (token_atual.tipo == TOKEN_ASTERISCO) {
            gerador_escrever("*");
            proximo();
            continue;
        }
        if (token_atual.tipo == TOKEN_E_COMERCIAL) {
            gerador_escrever("&");
            proximo();
            continue;
        }
        if (token_atual.tipo == TOKEN_NAO_LOGICO) {
            gerador_escrever("!");
            proximo();
            continue;
        }
        if (token_atual.tipo == TOKEN_MENOS) {
            gerador_escrever("-");
            proximo();
            continue; 
        }

        switch (token_atual.tipo) {
            case TOKEN_VALOR_INTEIRO:
            case TOKEN_VALOR_REAL:
                gerador_escrever(token_atual.lexema);
                proximo();
                break;

            case TOKEN_VALOR_CADEIA:
                traduzir_literal_cadeia(token_atual.lexema);
                proximo();
                break;

            case TOKEN_LER: {
                proximo(); 
                consumir(TOKEN_ABRE_PARENTESES, "Esperado '(' apos ler");
                if (token_atual.tipo == TOKEN_FECHA_PARENTESES) {
                    gerador_escrever("ler_numero()");
                } else {
                    gerador_escrever("ler_dados(&");
                    char nome_var[256];
                    strcpy(nome_var, token_atual.lexema);
                    proximo();
                    traduzir_acesso_identificador(nome_var, 0);
                    gerador_escrever(")");
                }
                consumir(TOKEN_FECHA_PARENTESES, "Esperado ')' apos ler");
                break;
            }

            case TOKEN_IDENTIFICADOR: {
                char nome[256];
                strcpy(nome, token_atual.lexema);
                proximo();
                
                if (strcmp(nome, "esperar") == 0) {
                    gerador_escrever("usleep"); 
                    gerador_escrever("(");
                    traduzir_expressao_ate(TOKEN_FECHA_PARENTESES);
                    gerador_escrever(" * 1000)"); 
                    proximo();
                }
                else {
                    traduzir_acesso_identificador(nome, 0);
                }
                break;
            }

            case TOKEN_ABRE_PARENTESES:
                gerador_escrever("(");
                proximo();
                traduzir_expressao_ate(TOKEN_FECHA_PARENTESES);
                gerador_escrever(")");
                proximo(); 
                break;

            case TOKEN_VERDADEIRO:
                gerador_escrever("1");
                proximo();
                break;

            case TOKEN_FALSO:
                gerador_escrever("0");
                proximo();
                break;

            case TOKEN_MAIS:
            case TOKEN_MENOS:
            case TOKEN_ASTERISCO:
            case TOKEN_BARRA:
            case TOKEN_PERCENTUAL:
            case TOKEN_IGUAL_IGUAL:
            case TOKEN_DIFERENTE:
            case TOKEN_MENOR:
            case TOKEN_MAIOR:
            case TOKEN_MENOR_IGUAL:
            case TOKEN_MAIOR_IGUAL:
            case TOKEN_E_LOGICO:
            case TOKEN_OU_LOGICO:
            case TOKEN_ATRIBUICAO:
            case TOKEN_SETA:
            case TOKEN_PONTO:
            case TOKEN_MAIS_MAIS:
            case TOKEN_MENOS_MENOS:
                traduzir_operador(token_atual.tipo);
                proximo();
                break;

            case TOKEN_VIRGULA:
                gerador_escrever(", ");
                proximo();
                break;

            default:
                return; 
        }
    }
}