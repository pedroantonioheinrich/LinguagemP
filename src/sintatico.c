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

void analisar(FILE* arquivo) {
    arquivo_global = arquivo;
    gerador_abrir("codigo_gerado.c");
    proximo();
    if (token_atual.tipo == TOKEN_INICIO) {
        proximo(); 
        consumir(TOKEN_ABRE_PARENTESES, "("); 
        consumir(TOKEN_FECHA_PARENTESES, ")");
        gerador_escrever("int main() ");
        bloco();
    }
    gerador_fechar();
    P_LOG_INFO("Analise Sintatica e Geracao de codigo concluidas com sucesso.");
}

int eh_palavra_reservada(TipoToken tipo) {
    return (tipo == TOKEN_SE || tipo == TOKEN_ENQUANTO || tipo == TOKEN_EXIBIR || 
            tipo == TOKEN_LER || tipo == TOKEN_LIGAR || tipo == TOKEN_DESLIGAR || 
            tipo == TOKEN_ESPERAR || tipo == TOKEN_RETORNE || tipo == TOKEN_INICIO || 
            tipo == TOKEN_INTEIRO || tipo == TOKEN_REAL || tipo == TOKEN_CONSTANTE ||
            tipo == TOKEN_SENAO);
}

void comando() {
    if (token_atual.tipo == TOKEN_CONSTANTE) {
        proximo();
        TipoToken t_base = token_atual.tipo;
        proximo();
        char n_const[100]; strcpy(n_const, token_atual.lexema);
        semantico_adicionar(n_const, t_base, token_atual.linha);
        semantico_marcar_constante(n_const);
        gerador_escrever(t_base == TOKEN_INTEIRO ? "const int " : "const float ");
        gerador_escrever(n_const); proximo();
        consumir(TOKEN_ATRIBUICAO, "="); gerador_escrever(" = ");
        while(token_atual.tipo != TOKEN_PONTO_VIRGULA) {
            gerador_escrever(" "); gerador_escrever(token_atual.lexema); gerador_escrever(" ");
            proximo();
        }
        gerador_escrever(";\n    "); consumir(TOKEN_PONTO_VIRGULA, ";");
    }
    else if (token_atual.tipo == TOKEN_INTEIRO || token_atual.tipo == TOKEN_REAL) {
        TipoToken t_decl = token_atual.tipo;
        proximo();
        char n_var[100]; strcpy(n_var, token_atual.lexema);
        semantico_adicionar(n_var, t_decl, token_atual.linha);
        gerador_escrever(t_decl == TOKEN_INTEIRO ? "int " : "float ");
        gerador_escrever(n_var); proximo();
        if (token_atual.tipo == TOKEN_ATRIBUICAO) {
            gerador_escrever(" = "); proximo();
            while(token_atual.tipo != TOKEN_PONTO_VIRGULA) {
                gerador_escrever(" "); gerador_escrever(token_atual.lexema); gerador_escrever(" ");
                proximo();
            }
        }
        gerador_escrever(";\n    "); consumir(TOKEN_PONTO_VIRGULA, ";");
    }
    else if (token_atual.tipo == TOKEN_SE || token_atual.tipo == TOKEN_ENQUANTO) {
        int loop = (token_atual.tipo == TOKEN_ENQUANTO);
        gerador_escrever(loop ? "while" : "if");
        proximo(); consumir(TOKEN_ABRE_PARENTESES, "("); gerador_escrever("(");
        while(token_atual.tipo != TOKEN_FECHA_PARENTESES) {
            gerador_escrever(" "); gerador_escrever(token_atual.lexema); gerador_escrever(" ");
            proximo();
        }
        gerador_escrever(")"); consumir(TOKEN_FECHA_PARENTESES, ")");
        bloco();
        if (!loop && token_atual.tipo == TOKEN_SENAO) { gerador_escrever("else"); proximo(); bloco(); }
    }
    else if (token_atual.tipo == TOKEN_IDENTIFICADOR && !eh_palavra_reservada(token_atual.tipo)) {
        char n_id[100]; strcpy(n_id, token_atual.lexema);
        proximo();
        if (token_atual.tipo == TOKEN_ATRIBUICAO) {
            if (!semantico_pode_atribuir(n_id)) { 
                char e_msg[256]; snprintf(e_msg, 256, "Erro Semantico: A constante '%s' nao pode ser alterada!", n_id);
                P_LOG_ERRO(e_msg); exit(1); 
            }
            gerador_escrever(n_id); gerador_escrever(" = "); proximo();
            while (token_atual.tipo != TOKEN_PONTO_VIRGULA) {
                gerador_escrever(" "); gerador_escrever(token_atual.lexema); gerador_escrever(" ");
                proximo();
            }
            gerador_escrever(";\n    "); consumir(TOKEN_PONTO_VIRGULA, ";");
        }
    }
    else if (token_atual.tipo == TOKEN_LIGAR || token_atual.tipo == TOKEN_DESLIGAR) {
        int lig = (token_atual.tipo == TOKEN_LIGAR); 
        proximo(); consumir(TOKEN_ABRE_PARENTESES, "(");
        gerador_escrever("printf(\"[HARDWARE] Pino %d: "); 
        gerador_escrever(lig ? "ON\\n\", (int)" : "OFF\\n\", (int)");
        gerador_escrever(token_atual.lexema); 
        proximo(); consumir(TOKEN_FECHA_PARENTESES, ")");
        gerador_escrever(");\n    "); 
        consumir(TOKEN_PONTO_VIRGULA, ";");
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
    else if (token_atual.tipo == TOKEN_RETORNE) {
        gerador_escrever("return "); proximo(); gerador_escrever(token_atual.lexema);
        proximo(); gerador_escrever(";\n    "); consumir(TOKEN_PONTO_VIRGULA, ";");
    }
    else { proximo(); }
}

void bloco() {
    consumir(TOKEN_ABRE_CHAVE, "{"); gerador_escrever(" {\n    ");
    while (token_atual.tipo != TOKEN_FECHA_CHAVE && token_atual.tipo != TOKEN_FIM) comando();
    consumir(TOKEN_FECHA_CHAVE, "}"); gerador_escrever("}\n\n");
}