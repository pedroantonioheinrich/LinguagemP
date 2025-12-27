#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sintatico.h"
#include "lexico.h"
#include "semantico.h"
#include "tradutores.h"
#include "gerador.h"

// Globais
Token token_atual;
Token token_lookahead;
int tem_lookahead = 0;
FILE* arquivo_fonte;
int escopo_global = 0;

extern int linha_atual;

// Protótipo antecipado
void comando();

void proximo() {
    if (tem_lookahead) {
        token_atual = token_lookahead;
        tem_lookahead = 0;
    } else {
        token_atual = proximo_token(arquivo_fonte);
    }
}

Token espiar() {
    if (!tem_lookahead) {
        token_lookahead = proximo_token(arquivo_fonte);
        tem_lookahead = 1;
    }
    return token_lookahead;
}

void consumir(TipoToken tipo, const char* msg) {
    if (token_atual.tipo == tipo) proximo();
    else {
        fprintf(stderr, "Erro Sintatico na linha %d: %s (Encontrado: %s, Lexema: %s)\n", 
                token_atual.linha, msg, tipo_token_para_string(token_atual.tipo), token_atual.lexema);
        exit(1);
    }
}

void bloco() {
    consumir(TOKEN_ABRE_CHAVE, "Esperado '{'");
    traduzir_abrir_bloco();
    while (token_atual.tipo != TOKEN_FECHA_CHAVE && token_atual.tipo != TOKEN_EOF) {
        comando();
    }
    consumir(TOKEN_FECHA_CHAVE, "Esperado '}'");
    traduzir_fechar_bloco();
}

void comando() {
    if (token_atual.tipo == TOKEN_PONTO_VIRGULA) {
        proximo();
        return;
    }

    // Suporte para o loop 'sempre' (Teste 19.lp)
    if (strcmp(token_atual.lexema, "sempre") == 0) {
        gerador_escrever("while (1) ");
        proximo();
        bloco();
        return;
    }

    // Tratamento unificado de RETORNO e RETORNE (Testes 40 e 68)
    if (token_atual.tipo == TOKEN_RETORNO || strcmp(token_atual.lexema, "retorne") == 0) {
        gerador_escrever("return ");
        proximo();
        if (token_atual.tipo != TOKEN_PONTO_VIRGULA && token_atual.tipo != TOKEN_FECHA_CHAVE) {
            traduzir_expressao_ate(TOKEN_PONTO_VIRGULA);
        }
        formatador_finalizar_instrucao();
        return;
    }

    switch (token_atual.tipo) {
        case TOKEN_EXIBIR:
            traduzir_comando_exibir();
            formatador_finalizar_instrucao();
            break;

        case TOKEN_LER: {
            proximo();
            consumir(TOKEN_ABRE_PARENTESES, "Esperado '(' apos ler");
            gerador_escrever("ler_dados("); 
            char nome_var[256];
            strcpy(nome_var, token_atual.lexema);
            proximo();
            traduzir_acesso_identificador(nome_var, 0);
            consumir(TOKEN_FECHA_PARENTESES, "Esperado ')'");
            gerador_escrever(")");
            formatador_finalizar_instrucao();
            break;
        }

        case TOKEN_PARA: {
            proximo();
            consumir(TOKEN_ABRE_PARENTESES, "Esperado '(' apos para");
            Token t_var = token_atual;
            proximo();
            if (token_atual.tipo == TOKEN_DE) {
                proximo();
                char inicio[50], fim[50];
                strcpy(inicio, token_atual.lexema); proximo();
                consumir(TOKEN_ATE, "Esperado 'ate'");
                strcpy(fim, token_atual.lexema); proximo();
                consumir(TOKEN_FECHA_PARENTESES, "Esperado ')'");
                gerador_escrever_formatado("for (%s = %s; %s <= %s; %s++) ", 
                    t_var.lexema, inicio, t_var.lexema, fim, t_var.lexema);
            } else {
                gerador_escrever("for (");
                gerador_escrever(t_var.lexema);
                traduzir_expressao_ate(TOKEN_PONTO_VIRGULA);
                gerador_escrever("; "); proximo(); 
                traduzir_expressao_ate(TOKEN_PONTO_VIRGULA);
                gerador_escrever("; "); proximo(); 
                traduzir_expressao_ate(TOKEN_FECHA_PARENTESES);
                gerador_escrever(") "); proximo(); 
            }
            bloco();
            break;
        }

        case TOKEN_SE:
            traduzir_inicio_se();
            bloco();
            if (token_atual.tipo == TOKEN_SENAO) {
                proximo();
                if (token_atual.tipo == TOKEN_SE) comando();
                else bloco();
            }
            break;

        case TOKEN_ENQUANTO:
            traduzir_inicio_enquanto();
            bloco();
            break;

        case TOKEN_INTEIRO:
        case TOKEN_REAL:
        case TOKEN_CADEIA:
        case TOKEN_LOGICO:
        case TOKEN_VAZIO:
            traduzir_declaracao_variavel();
            if (token_atual.tipo == TOKEN_ATRIBUICAO) {
                gerador_escrever(" = ");
                proximo();
                traduzir_expressao_ate(TOKEN_PONTO_VIRGULA);
            }
            formatador_finalizar_instrucao();
            break;

        case TOKEN_IDENTIFICADOR: {
            if (strcmp(token_atual.lexema, "usar") == 0) {
                proximo(); proximo(); 
                return;
            }
            Token prox = espiar();
            if (prox.tipo == TOKEN_IDENTIFICADOR) {
                traduzir_declaracao_variavel();
                if (token_atual.tipo == TOKEN_ATRIBUICAO) {
                    gerador_escrever(" = ");
                    proximo();
                    traduzir_expressao_ate(TOKEN_PONTO_VIRGULA);
                }
            } else {
                char nome[256];
                strcpy(nome, token_atual.lexema);
                proximo();
                traduzir_acesso_identificador(nome, 0);

                if (token_atual.tipo == TOKEN_MAIS_MAIS || token_atual.tipo == TOKEN_MENOS_MENOS) {
                    gerador_escrever(token_atual.lexema);
                    proximo();
                } 
                else if (token_atual.tipo == TOKEN_ATRIBUICAO) {
                    gerador_escrever(" = ");
                    proximo();
                    traduzir_expressao_ate(TOKEN_PONTO_VIRGULA);
                }
            }
            formatador_finalizar_instrucao();
            break;
        }
        default: proximo(); break;
    }
}

void analisar(FILE* arquivo) {
    arquivo_fonte = arquivo;
    linha_atual = 1; 
    gerador_abrir("codigo_gerado.c");
    
    gerador_escrever("#include <stdio.h>\n#include <stdbool.h>\n#include <string.h>\n#include <stdlib.h>\n#include <unistd.h>\n\n");
    gerador_escrever("// Funcoes de Suporte (Runtime)\n");
    gerador_escrever("#define iguais(s1, s2) (strcmp(s1, s2) == 0)\n");
    gerador_escrever("#define juntar(dest, src) strcat(dest, src)\n");
    gerador_escrever("void ligar(int p) { printf(\"LED %d ON\\n\", p); }\n");
    gerador_escrever("void desligar(int p) { printf(\"LED %d OFF\\n\", p); }\n");
    gerador_escrever("void esperar(int ms) { usleep(ms * 1000); }\n");
    gerador_escrever("void exibir_alerta(const char* m) { printf(\"ALERTA: %s\\n\", m); }\n");
    gerador_escrever("double ler_numero() { double n; scanf(\"%lf\", &n); return n; }\n");
    gerador_escrever("void ler_dados(char* b) { scanf(\" %s\", b); }\n\n");
    
    proximo();
    while (token_atual.tipo != TOKEN_EOF) {
        if (token_atual.tipo == TOKEN_REGISTRO) {
            traduzir_definicao_registro();
        } else if (token_atual.tipo == TOKEN_FUNCAO) {
            traduzir_declaracao_funcao();
        } else if (token_atual.tipo == TOKEN_INICIO) {
            proximo();
            if (token_atual.tipo == TOKEN_ABRE_PARENTESES) {
                consumir(TOKEN_ABRE_PARENTESES, "Esperado '('");
                consumir(TOKEN_FECHA_PARENTESES, "Esperado ')'");
            }
            gerador_escrever("int main() ");
            bloco();
        } else if (token_atual.tipo == TOKEN_IDENTIFICADOR && strcmp(token_atual.lexema, "usar") == 0) {
            proximo(); proximo();
        } else {
            proximo();
        }
    }
    gerador_fechar();
}