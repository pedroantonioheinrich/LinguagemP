#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sintatico.h"
#include "lexico.h"
#include "gerador.h"
#include "semantico.h"
#include "logs.h"

// Variáveis Globais de Controle
Token token_atual;
Token token_lookahead;
int tem_lookahead = 0;
FILE* arquivo_global;
int escopo_atual = 0; 

// --- PROTÓTIPOS ---
void comando();
void bloco();
void declaracao_variavel();
void declaracao_registro();
void declaracao_funcao();
void copiar_expressao_ate(TipoToken limitador);

// --- FUNÇÕES DE SUPORTE ---

void proximo() {
    if (tem_lookahead) { 
        token_atual = token_lookahead; 
        tem_lookahead = 0; 
    } else { 
        token_atual = proximo_token(arquivo_global); 
    }
}

Token espiar() {
    if (!tem_lookahead) {
        token_lookahead = proximo_token(arquivo_global);
        tem_lookahead = 1;
    }
    return token_lookahead;
}

void consumir(TipoToken tipo, const char* msg) {
    if (token_atual.tipo == tipo) {
        proximo();
    } else { 
        char erro[512];
        snprintf(erro, 512, "Erro Sintatico na linha %d: %s (Recebeu: '%s')", 
                 token_atual.linha, msg, token_atual.lexema);
        P_LOG_ERRO(erro); 
        exit(1); 
    }
}

void copiar_expressao_ate(TipoToken limitador) {
    int nivel_p = 0;
    while(token_atual.tipo != TOKEN_FIM) {
        if (token_atual.tipo == limitador && nivel_p == 0) break;
        if (token_atual.tipo == TOKEN_ABRE_PARENTESES) nivel_p++;
        else if (token_atual.tipo == TOKEN_FECHA_PARENTESES) nivel_p--;

        gerador_escrever(token_atual.lexema);
        gerador_escrever(" ");
        proximo();
    }
}

// --- REGRAS GRAMATICAIS ---

void declaracao_funcao() {
    consumir(TOKEN_FUNCAO, "funcao");
    
    // Tradução do tipo de retorno para C
    if (token_atual.tipo == TOKEN_INTEIRO) gerador_escrever("int ");
    else if (token_atual.tipo == TOKEN_REAL) gerador_escrever("float ");
    else if (token_atual.tipo == TOKEN_CADEIA) gerador_escrever("char* ");
    else gerador_escrever("void ");
    proximo();

    // Nome da função
    gerador_escrever(token_atual.lexema);
    proximo();

    // Tradução dos Parâmetros (Linguagem P -> C)
    consumir(TOKEN_ABRE_PARENTESES, "(");
    gerador_escrever("(");
    while(token_atual.tipo != TOKEN_FECHA_PARENTESES && token_atual.tipo != TOKEN_FIM) {
        if (token_atual.tipo == TOKEN_INTEIRO) gerador_escrever("int ");
        else if (token_atual.tipo == TOKEN_REAL) gerador_escrever("float ");
        else if (token_atual.tipo == TOKEN_CADEIA) gerador_escrever("char* ");
        else gerador_escrever(token_atual.lexema); 
        
        gerador_escrever(" ");
        proximo();
    }
    gerador_escrever(")");
    consumir(TOKEN_FECHA_PARENTESES, ")");

    bloco();
    gerador_escrever("\n");
}

void declaracao_variavel() {
    TipoToken t = token_atual.tipo;
    char nome_var[100];
    char tipo_reg_nome[100] = "";
    
    if (t == TOKEN_IDENTIFICADOR) { // Registros
        strcpy(tipo_reg_nome, token_atual.lexema);
        gerador_escrever(tipo_reg_nome); gerador_escrever(" "); 
        proximo();
        strcpy(nome_var, token_atual.lexema);
        semantico_adicionar_com_tipo_reg(nome_var, tipo_reg_nome, escopo_atual);
        gerador_escrever(nome_var); 
        proximo();
    } 
    else { // Primitivos
        if (t == TOKEN_CADEIA) gerador_escrever("char ");
        else if (t == TOKEN_INTEIRO) gerador_escrever("int ");
        else if (t == TOKEN_REAL) gerador_escrever("float ");
        proximo();
        
        strcpy(nome_var, token_atual.lexema);
        semantico_adicionar(nome_var, t, escopo_atual);
        gerador_escrever(nome_var); 
        proximo();
        
        // Suporte a Vetores (ex: inteiro notas[10])
        if (token_atual.tipo == TOKEN_ABRE_COLCHETE) {
            gerador_escrever("["); proximo();
            gerador_escrever(token_atual.lexema); proximo();
            consumir(TOKEN_FECHA_COLCHETE, "]");
            gerador_escrever("]");
        } else if (t == TOKEN_CADEIA) {
            gerador_escrever("[256]"); 
        }
    }
    gerador_escrever(";\n    ");
    if (token_atual.tipo == TOKEN_PONTO_VIRGULA) proximo();
}

void comando() {
    if (token_atual.tipo == TOKEN_LEIA) {
        proximo(); consumir(TOKEN_ABRE_PARENTESES, "(");
        char v[100]; strcpy(v, token_atual.lexema);
        TipoToken t = semantico_obter_tipo(v);
        if (t == TOKEN_INTEIRO) gerador_escrever("scanf(\"%d\", &");
        else if (t == TOKEN_REAL) gerador_escrever("scanf(\"%f\", &");
        else gerador_escrever("scanf(\" %[^\\n]\", "); 
        gerador_escrever(v); proximo(); 
        consumir(TOKEN_FECHA_PARENTESES, ")");
        gerador_escrever(");\n    "); 
        consumir(TOKEN_PONTO_VIRGULA, ";");
    }
    else if (token_atual.tipo == TOKEN_SE) {
        proximo(); consumir(TOKEN_ABRE_PARENTESES, "(");
        gerador_escrever("if ("); 
        copiar_expressao_ate(TOKEN_FECHA_PARENTESES);
        gerador_escrever(") "); 
        consumir(TOKEN_FECHA_PARENTESES, ")");
        bloco();
        if (token_atual.tipo == TOKEN_SENAO) { 
            gerador_escrever(" else "); proximo(); 
            if (token_atual.tipo == TOKEN_SE) comando();
            else bloco(); 
        }
    }
    else if (token_atual.tipo == TOKEN_ENQUANTO) {
        proximo(); consumir(TOKEN_ABRE_PARENTESES, "(");
        gerador_escrever("while (");
        copiar_expressao_ate(TOKEN_FECHA_PARENTESES);
        gerador_escrever(") ");
        consumir(TOKEN_FECHA_PARENTESES, ")");
        bloco();
    }
    else if (token_atual.tipo == TOKEN_PARA) {
        proximo(); consumir(TOKEN_ABRE_PARENTESES, "(");
        char v_c[100]; strcpy(v_c, token_atual.lexema); proximo();
        consumir(TOKEN_DE, "de"); 
        char ini[50]; strcpy(ini, token_atual.lexema); proximo();
        consumir(TOKEN_ATE, "ate"); 
        char fim_loop[50]; strcpy(fim_loop, token_atual.lexema); proximo();
        consumir(TOKEN_FECHA_PARENTESES, ")");
        gerador_escrever("for ("); gerador_escrever(v_c); gerador_escrever(" = "); gerador_escrever(ini);
        gerador_escrever("; "); gerador_escrever(v_c); gerador_escrever(" < "); gerador_escrever(fim_loop);
        gerador_escrever("; "); gerador_escrever(v_c); gerador_escrever("++)"); 
        bloco();
    }
    else if (token_atual.tipo == TOKEN_EXIBIR) {
        proximo(); consumir(TOKEN_ABRE_PARENTESES, "(");
        char expressao[512] = "";
        int eh_str = 0; int nivel_p = 0;
        while(token_atual.tipo != TOKEN_FIM) {
            if (token_atual.tipo == TOKEN_FECHA_PARENTESES && nivel_p == 0) break;
            if (token_atual.tipo == TOKEN_ABRE_PARENTESES) nivel_p++;
            else if (token_atual.tipo == TOKEN_FECHA_PARENTESES) nivel_p--;
            if (token_atual.lexema[0] == '"' || semantico_obter_tipo(token_atual.lexema) == TOKEN_CADEIA || strstr(token_atual.lexema, "nome")) eh_str = 1;
            strcat(expressao, token_atual.lexema); strcat(expressao, " ");
            proximo();
        }
        if (eh_str) { gerador_escrever("printf(\"%s\\n\", "); gerador_escrever(expressao); gerador_escrever(")"); }
        else { gerador_escrever("printf(\"%g\\n\", (double)("); gerador_escrever(expressao); gerador_escrever("))"); }
        gerador_escrever(";\n    "); 
        consumir(TOKEN_FECHA_PARENTESES, ")"); consumir(TOKEN_PONTO_VIRGULA, ";");
    }
    else if (token_atual.tipo == TOKEN_RETORNO) {
        proximo(); gerador_escrever("return ");
        copiar_expressao_ate(TOKEN_PONTO_VIRGULA);
        gerador_escrever(";\n    ");
        consumir(TOKEN_PONTO_VIRGULA, ";");
    }
    else if (token_atual.tipo == TOKEN_IDENTIFICADOR) {
        char n1[200]; strcpy(n1, token_atual.lexema);
        if (semantico_existe_registro(n1) && espiar().tipo == TOKEN_IDENTIFICADOR) {
            declaracao_variavel(); return;
        }
        proximo();
        
        // Suporte a acesso de Vetor na Atribuição (ex: notas[0] = 10)
        if (token_atual.tipo == TOKEN_ABRE_COLCHETE) {
            strcat(n1, "["); proximo();
            strcat(n1, token_atual.lexema); proximo();
            consumir(TOKEN_FECHA_COLCHETE, "]");
            strcat(n1, "]");
        }
        
        // Acesso a membros de registro
        while (token_atual.tipo == TOKEN_PONTO) {
            strcat(n1, "."); proximo();
            strcat(n1, token_atual.lexema); proximo();
        }
        
        if (token_atual.tipo == TOKEN_ATRIBUICAO) {
            proximo();
            if (token_atual.lexema[0] == '"') {
                gerador_escrever("strcpy("); gerador_escrever(n1); gerador_escrever(", "); 
                gerador_escrever(token_atual.lexema); gerador_escrever(")"); proximo();
            } else {
                gerador_escrever(n1); gerador_escrever(" = "); 
                copiar_expressao_ate(TOKEN_PONTO_VIRGULA);
            }
            gerador_escrever(";\n    "); 
            consumir(TOKEN_PONTO_VIRGULA, ";");
        } else if (token_atual.tipo == TOKEN_ABRE_PARENTESES) {
            gerador_escrever(n1); gerador_escrever("("); proximo();
            copiar_expressao_ate(TOKEN_FECHA_PARENTESES);
            gerador_escrever(")"); proximo(); gerador_escrever(";\n    ");
            if (token_atual.tipo == TOKEN_PONTO_VIRGULA) proximo();
        }
    } 
    else if (token_atual.tipo == TOKEN_INTEIRO || token_atual.tipo == TOKEN_REAL || token_atual.tipo == TOKEN_CADEIA) {
        declaracao_variavel();
    }
    else proximo();
}

void bloco() {
    consumir(TOKEN_ABRE_CHAVE, "{"); 
    gerador_escrever(" {\n    ");
    while (token_atual.tipo != TOKEN_FECHA_CHAVE && token_atual.tipo != TOKEN_FIM) {
        comando();
    }
    gerador_escrever("}\n    "); 
    consumir(TOKEN_FECHA_CHAVE, "}");
}

void declaracao_registro() {
    consumir(TOKEN_REGISTRO, "registro");
    char n[100]; strcpy(n, token_atual.lexema); 
    semantico_definir_registro(n);
    gerador_escrever("typedef struct {\n"); 
    proximo(); 
    consumir(TOKEN_ABRE_CHAVE, "{");
    while (token_atual.tipo != TOKEN_FECHA_CHAVE) {
        TipoToken tipo_campo = token_atual.tipo;
        if (tipo_campo == TOKEN_CADEIA) gerador_escrever("    char ");
        else gerador_escrever(tipo_campo == TOKEN_INTEIRO ? "    int " : "    float ");
        proximo(); 
        char campo[100]; strcpy(campo, token_atual.lexema);
        gerador_escrever(campo);
        if (tipo_campo == TOKEN_CADEIA || strstr(campo, "nome")) gerador_escrever("[256]");
        gerador_escrever(";\n"); 
        proximo();
        if (token_atual.tipo == TOKEN_PONTO_VIRGULA) proximo();
    }
    gerador_escrever("} "); gerador_escrever(n); gerador_escrever(";\n\n");
    consumir(TOKEN_FECHA_CHAVE, "}");
}

void analisar(FILE* arquivo) {
    arquivo_global = arquivo; 
    gerador_abrir("codigo_gerado.c");
    gerador_escrever("#include <stdio.h>\n#include <string.h>\n#include <stdlib.h>\n\n");
    proximo();
    while (token_atual.tipo != TOKEN_FIM) {
        if (token_atual.tipo == TOKEN_REGISTRO) declaracao_registro();
        else if (token_atual.tipo == TOKEN_FUNCAO) declaracao_funcao();
        else if (token_atual.tipo == TOKEN_INICIO) {
            escopo_atual = 1;
            proximo(); consumir(TOKEN_ABRE_PARENTESES, "("); consumir(TOKEN_FECHA_PARENTESES, ")");
            gerador_escrever("int main() {\n    ");
            bloco(); 
            gerador_escrever("\n    return 0;\n}\n");
            escopo_atual = 0;
        } 
        else if (token_atual.tipo == TOKEN_INTEIRO || token_atual.tipo == TOKEN_REAL || token_atual.tipo == TOKEN_CADEIA) {
            declaracao_variavel();
        } 
        else proximo();
    }
    gerador_fechar();
    P_LOG_INFO("V28.0: Integrado suporte a Funcoes, Vetores e Registros.");
}