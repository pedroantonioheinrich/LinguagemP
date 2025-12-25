#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sintatico.h"
#include "lexico.h"
#include "gerador.h"
#include "semantico.h"
#include "logs.h"

Token token_atual;
FILE* arquivo_global;

void proximo() { token_atual = proximo_token(arquivo_global); }

void consumir(TipoToken tipo, const char* msg) {
    if (token_atual.tipo == tipo) proximo();
    else { 
        char erro[512];
        snprintf(erro, 512, "Erro Sintatico na linha %d: %s (Recebeu: '%s')", token_atual.linha, msg, token_atual.lexema);
        P_LOG_ERRO(erro); exit(1); 
    }
}

void comando();
void bloco();

void processar_expressao_logica() {
    while(token_atual.tipo != TOKEN_FECHA_PARENTESES && token_atual.tipo != TOKEN_PONTO_VIRGULA) {
        if (token_atual.tipo == TOKEN_E) gerador_escrever(" && ");
        else if (token_atual.tipo == TOKEN_OU) gerador_escrever(" || ");
        else { gerador_escrever(" "); gerador_escrever(token_atual.lexema); gerador_escrever(" "); }
        proximo();
    }
}

void comando_para() {
    consumir(TOKEN_PARA, "para");
    consumir(TOKEN_ABRE_PARENTESES, "(");
    gerador_escrever("for (");
    if (token_atual.tipo == TOKEN_INTEIRO || token_atual.tipo == TOKEN_REAL) {
        TipoToken t = token_atual.tipo; proximo();
        gerador_escrever(t == TOKEN_INTEIRO ? "int " : "float ");
        gerador_escrever(token_atual.lexema);
        semantico_adicionar(token_atual.lexema, t, token_atual.linha);
        proximo(); consumir(TOKEN_ATRIBUICAO, "="); gerador_escrever(" = ");
    }
    while(token_atual.tipo != TOKEN_PONTO_VIRGULA) { gerador_escrever(token_atual.lexema); proximo(); }
    gerador_escrever("; "); consumir(TOKEN_PONTO_VIRGULA, ";");
    processar_expressao_logica();
    gerador_escrever("; "); consumir(TOKEN_PONTO_VIRGULA, ";");
    while(token_atual.tipo != TOKEN_FECHA_PARENTESES) { gerador_escrever(token_atual.lexema); proximo(); }
    gerador_escrever(") "); consumir(TOKEN_FECHA_PARENTESES, ")");
    bloco();
}

void comando() {
    if (token_atual.tipo == TOKEN_INTEIRO || token_atual.tipo == TOKEN_REAL) {
        TipoToken t_decl = token_atual.tipo; proximo();
        char n_var[100]; strcpy(n_var, token_atual.lexema);
        semantico_adicionar(n_var, t_decl, token_atual.linha);
        gerador_escrever(t_decl == TOKEN_INTEIRO ? "int " : "float ");
        gerador_escrever(n_var); proximo();
        if (token_atual.tipo == TOKEN_ATRIBUICAO) {
            proximo();
            if (token_atual.tipo == TOKEN_LER) {
                proximo(); consumir(TOKEN_ABRE_PARENTESES, "("); consumir(TOKEN_FECHA_PARENTESES, ")");
                gerador_escrever("; printf(\"Entrada: \"); scanf(\"");
                gerador_escrever(t_decl == TOKEN_INTEIRO ? "%d\", &" : "%f\", &");
                gerador_escrever(n_var); gerador_escrever(")");
            } else {
                gerador_escrever(" = ");
                while(token_atual.tipo != TOKEN_PONTO_VIRGULA) { gerador_escrever(token_atual.lexema); proximo(); }
            }
        }
        gerador_escrever(";\n    "); consumir(TOKEN_PONTO_VIRGULA, ";");
    }
    else if (token_atual.tipo == TOKEN_SE || token_atual.tipo == TOKEN_ENQUANTO) {
        gerador_escrever(token_atual.tipo == TOKEN_ENQUANTO ? "while (" : "if (");
        proximo(); consumir(TOKEN_ABRE_PARENTESES, "(");
        processar_expressao_logica();
        gerador_escrever(")"); consumir(TOKEN_FECHA_PARENTESES, ")");
        bloco();
        if (token_atual.tipo == TOKEN_SENAO) { gerador_escrever("else "); proximo(); bloco(); }
    }
    else if (token_atual.tipo == TOKEN_PARA) { comando_para(); }
    else if (token_atual.tipo == TOKEN_IDENTIFICADOR) {
        char n_id[100]; strcpy(n_id, token_atual.lexema);
        proximo();
        if (token_atual.tipo == TOKEN_ATRIBUICAO) {
            if (!semantico_pode_atribuir(n_id)) { P_LOG_ERRO("Erro: Constante!"); exit(1); }
            gerador_escrever(n_id); 
            proximo();
            if (token_atual.tipo == TOKEN_LER) {
                proximo(); consumir(TOKEN_ABRE_PARENTESES, "("); consumir(TOKEN_FECHA_PARENTESES, ")");
                Simbolo* s = semantico_buscar(n_id);
                gerador_escrever(" = 0; scanf(\"");
                gerador_escrever(s->tipo == TOKEN_INTEIRO ? "%d\", &" : "%f\", &");
                gerador_escrever(n_id); gerador_escrever(")");
            } else {
                gerador_escrever(" = ");
                while(token_atual.tipo != TOKEN_PONTO_VIRGULA) { gerador_escrever(token_atual.lexema); proximo(); }
            }
            gerador_escrever(";\n    "); consumir(TOKEN_PONTO_VIRGULA, ";");
        }
    }
    else if (token_atual.tipo == TOKEN_EXIBIR) {
        proximo(); consumir(TOKEN_ABRE_PARENTESES, "(");
        if (token_atual.tipo == TOKEN_CADEIA) {
            gerador_escrever("printf(\"%s\\n\", \""); gerador_escrever(token_atual.lexema); gerador_escrever("\")");
        } else {
            gerador_escrever("printf(\"%g\\n\", (double)"); gerador_escrever(token_atual.lexema); gerador_escrever(")");
        }
        proximo(); consumir(TOKEN_FECHA_PARENTESES, ")"); gerador_escrever(";\n    "); consumir(TOKEN_PONTO_VIRGULA, ";");
    }
    else if (token_atual.tipo == TOKEN_ESPERAR) {
        proximo(); consumir(TOKEN_ABRE_PARENTESES, "(");
        gerador_escrever("usleep("); gerador_escrever(token_atual.lexema); gerador_escrever(" * 1000)");
        proximo(); consumir(TOKEN_FECHA_PARENTESES, ")"); gerador_escrever(";\n    "); consumir(TOKEN_PONTO_VIRGULA, ";");
    }
    else { proximo(); }
}

void bloco() {
    consumir(TOKEN_ABRE_CHAVE, "{"); gerador_escrever(" {\n    ");
    while (token_atual.tipo != TOKEN_FECHA_CHAVE && token_atual.tipo != TOKEN_FIM) comando();
    consumir(TOKEN_FECHA_CHAVE, "}"); gerador_escrever("}\n\n");
}

void analisar(FILE* arquivo) {
    arquivo_global = arquivo;
    gerador_abrir("codigo_gerado.c");
    proximo();
    if (token_atual.tipo == TOKEN_INICIO) {
        proximo(); consumir(TOKEN_ABRE_PARENTESES, "("); consumir(TOKEN_FECHA_PARENTESES, ")");
        gerador_escrever("int main() ");
        bloco();
    }
    gerador_fechar();
    P_LOG_INFO("Analise Sintatica v1.2 concluida.");
}