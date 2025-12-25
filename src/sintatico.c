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

// Auxiliar para copiar expressões até um delimitador
void copiar_expressao_ate(TipoToken limitador) {
    while(token_atual.tipo != limitador && token_atual.tipo != TOKEN_FIM) {
        if (token_atual.tipo == TOKEN_IGUAL) gerador_escrever(" == ");
        else {
            gerador_escrever(" ");
            gerador_escrever(token_atual.lexema);
            gerador_escrever(" ");
        }
        proximo();
    }
}

void declaracao_funcao() {
    consumir(TOKEN_FUNCAO, "funcao");
    TipoToken tipo_ret = token_atual.tipo;
    if (tipo_ret == TOKEN_INTEIRO) gerador_escrever("int ");
    else if (tipo_ret == TOKEN_REAL) gerador_escrever("float ");
    else gerador_escrever("void ");
    proximo();

    char nome_f[100]; strcpy(nome_f, token_atual.lexema);
    int linha_f = token_atual.linha;
    proximo();

    consumir(TOKEN_ABRE_PARENTESES, "(");
    gerador_escrever(nome_f); gerador_escrever("(");

    int n_params = 0;
    while (token_atual.tipo == TOKEN_INTEIRO || token_atual.tipo == TOKEN_REAL) {
        if (n_params > 0) gerador_escrever(", ");
        gerador_escrever(token_atual.tipo == TOKEN_INTEIRO ? "int " : "float ");
        proximo();
        gerador_escrever(token_atual.lexema);
        semantico_adicionar(token_atual.lexema, TOKEN_VALOR, token_atual.linha);
        n_params++;
        proximo();
        if (token_atual.tipo == TOKEN_VIRGULA) { proximo(); }
    }
    
    semantico_adicionar_funcao(nome_f, tipo_ret, n_params, linha_f);
    gerador_escrever(")");
    consumir(TOKEN_FECHA_PARENTESES, ")");
    bloco();
}

void comando_para() {
    consumir(TOKEN_PARA, "para");
    consumir(TOKEN_ABRE_PARENTESES, "(");

    char var_controle[100];
    strcpy(var_controle, token_atual.lexema);
    proximo();

    if (token_atual.tipo == TOKEN_ATRIBUICAO) {
        // PADRÃO 1: estilo C
        gerador_escrever("for (");
        gerador_escrever(var_controle);
        gerador_escrever(" = ");
        proximo();
        copiar_expressao_ate(TOKEN_PONTO_VIRGULA);
        gerador_escrever(";");
        consumir(TOKEN_PONTO_VIRGULA, ";");
        copiar_expressao_ate(TOKEN_PONTO_VIRGULA);
        gerador_escrever(";");
        consumir(TOKEN_PONTO_VIRGULA, ";");
        copiar_expressao_ate(TOKEN_FECHA_PARENTESES);
        gerador_escrever(")");
    } 
    else if (token_atual.tipo == TOKEN_DE) {
        // PADRÃO 2: estilo simplificado
        consumir(TOKEN_DE, "de");
        char valor_inicial[100];
        strcpy(valor_inicial, token_atual.lexema);
        proximo();
        
        consumir(TOKEN_ATE, "ate");
        char valor_final[100];
        strcpy(valor_final, token_atual.lexema);
        proximo();

        gerador_escrever("for (");
        gerador_escrever(var_controle);
        gerador_escrever(" = ");
        gerador_escrever(valor_inicial);
        gerador_escrever("; ");
        gerador_escrever(var_controle);
        gerador_escrever(" <= ");
        gerador_escrever(valor_final);
        gerador_escrever("; ");
        gerador_escrever(var_controle);
        gerador_escrever("++)");
    }
    consumir(TOKEN_FECHA_PARENTESES, ")");
    bloco();
}

void comando() {
    if (token_atual.tipo == TOKEN_PARA) {
        comando_para();
    }
    else if (token_atual.tipo == TOKEN_SE) {
        gerador_escrever("if ("); proximo();
        consumir(TOKEN_ABRE_PARENTESES, "(");
        copiar_expressao_ate(TOKEN_FECHA_PARENTESES);
        gerador_escrever(")");
        consumir(TOKEN_FECHA_PARENTESES, ")");
        bloco();
        if (token_atual.tipo == TOKEN_SENAO) {
            gerador_escrever("else "); proximo();
            if (token_atual.tipo == TOKEN_SE) comando();
            else bloco();
        }
    }
    else if (token_atual.tipo == TOKEN_ENQUANTO) {
        gerador_escrever("while ("); proximo();
        consumir(TOKEN_ABRE_PARENTESES, "(");
        copiar_expressao_ate(TOKEN_FECHA_PARENTESES);
        gerador_escrever(")");
        consumir(TOKEN_FECHA_PARENTESES, ")");
        bloco();
    }
    else if (token_atual.tipo == TOKEN_IDENTIFICADOR) {
        char n_id[100]; strcpy(n_id, token_atual.lexema);
        int lin = token_atual.linha;
        proximo();
        
        if (token_atual.tipo == TOKEN_ABRE_PARENTESES) {
            gerador_escrever(n_id); gerador_escrever("(");
            int n_p = 0; proximo();
            while(token_atual.tipo != TOKEN_FECHA_PARENTESES) {
                if (n_p > 0 && token_atual.tipo != TOKEN_VIRGULA) gerador_escrever(" ");
                gerador_escrever(token_atual.lexema);
                if (token_atual.tipo != TOKEN_VIRGULA) n_p++;
                proximo();
                if (token_atual.tipo == TOKEN_VIRGULA) { gerador_escrever(", "); proximo(); }
            }
            semantico_validar_chamada(n_id, n_p, lin);
            gerador_escrever(")"); proximo();
            gerador_escrever(";\n    "); consumir(TOKEN_PONTO_VIRGULA, ";");
        } 
        else if (token_atual.tipo == TOKEN_ATRIBUICAO) {
            gerador_escrever(n_id); gerador_escrever(" = "); proximo();
            while(token_atual.tipo != TOKEN_PONTO_VIRGULA) {
                gerador_escrever(token_atual.lexema); gerador_escrever(" ");
                proximo();
            }
            gerador_escrever(";\n    "); consumir(TOKEN_PONTO_VIRGULA, ";");
        }
    }
    else if (token_atual.tipo == TOKEN_INTEIRO || token_atual.tipo == TOKEN_REAL) {
        TipoToken t = token_atual.tipo; proximo();
        char var[100]; strcpy(var, token_atual.lexema);
        semantico_adicionar(var, t, token_atual.linha);
        gerador_escrever(t == TOKEN_INTEIRO ? "int " : "float ");
        gerador_escrever(var); proximo();
        if (token_atual.tipo == TOKEN_ATRIBUICAO) {
            gerador_escrever(" = "); proximo();
            if (token_atual.tipo == TOKEN_LER) {
                proximo(); consumir(TOKEN_ABRE_PARENTESES, "("); consumir(TOKEN_FECHA_PARENTESES, ")");
                gerador_escrever(t == TOKEN_INTEIRO ? "0; scanf(\"%d\", &" : "0.0; scanf(\"%f\", &");
                gerador_escrever(var); gerador_escrever(")");
            } else {
                while(token_atual.tipo != TOKEN_PONTO_VIRGULA) { 
                    gerador_escrever(token_atual.lexema); proximo(); 
                }
            }
        }
        gerador_escrever(";\n    "); consumir(TOKEN_PONTO_VIRGULA, ";");
    }
    else if (token_atual.tipo == TOKEN_RETORNE) {
        gerador_escrever("return "); proximo();
        while(token_atual.tipo != TOKEN_PONTO_VIRGULA) { 
            gerador_escrever(token_atual.lexema); proximo(); 
        }
        gerador_escrever(";\n    "); consumir(TOKEN_PONTO_VIRGULA, ";");
    }
    else if (token_atual.tipo == TOKEN_EXIBIR) {
        proximo(); consumir(TOKEN_ABRE_PARENTESES, "(");
        if (token_atual.tipo == TOKEN_CADEIA) {
            gerador_escrever("printf(\"%s\\n\", \""); gerador_escrever(token_atual.lexema); gerador_escrever("\")");
            proximo();
        } else {
            gerador_escrever("printf(\"%g\\n\", (double)(");
            while(token_atual.tipo != TOKEN_FECHA_PARENTESES) {
                gerador_escrever(token_atual.lexema); proximo();
            }
            gerador_escrever("))");
        }
        consumir(TOKEN_FECHA_PARENTESES, ")"); gerador_escrever(";\n    "); consumir(TOKEN_PONTO_VIRGULA, ";");
    }
}

void bloco() {
    consumir(TOKEN_ABRE_CHAVE, "{"); gerador_escrever(" {\n    ");
    while (token_atual.tipo != TOKEN_FECHA_CHAVE && token_atual.tipo != TOKEN_FIM) comando();
    gerador_escrever("}\n    "); consumir(TOKEN_FECHA_CHAVE, "}"); 
}

void analisar(FILE* arquivo) {
    arquivo_global = arquivo;
    gerador_abrir("codigo_gerado.c");
    gerador_escrever("#include <stdio.h>\n#include <unistd.h>\n\n");
    proximo();
    while (token_atual.tipo != TOKEN_FIM) {
        if (token_atual.tipo == TOKEN_FUNCAO) declaracao_funcao();
        else if (token_atual.tipo == TOKEN_INICIO) {
            proximo(); consumir(TOKEN_ABRE_PARENTESES, "("); consumir(TOKEN_FECHA_PARENTESES, ")");
            gerador_escrever("int main() "); bloco();
        } else proximo();
    }
    gerador_fechar();
    P_LOG_INFO("V1.6: Suporte a funcoes, condicionais e loops (para/enquanto) concluidos.");
}