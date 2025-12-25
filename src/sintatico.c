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

void declaracao_funcao() {
    consumir(TOKEN_FUNCAO, "funcao");
    TipoToken tipo_ret = token_atual.tipo;
    if (tipo_ret == TOKEN_INTEIRO) gerador_escrever("int ");
    else if (tipo_ret == TOKEN_REAL) gerador_escrever("float ");
    else gerador_escrever("void ");
    proximo();
    char nome_funcao[100];
    strcpy(nome_funcao, token_atual.lexema);
    semantico_adicionar_funcao(nome_funcao, tipo_ret, token_atual.linha);
    gerador_escrever(nome_funcao);
    proximo();
    consumir(TOKEN_ABRE_PARENTESES, "(");
    gerador_escrever("(");
    if (token_atual.tipo == TOKEN_INTEIRO || token_atual.tipo == TOKEN_REAL) {
        gerador_escrever(token_atual.tipo == TOKEN_INTEIRO ? "int " : "float ");
        proximo();
        gerador_escrever(token_atual.lexema);
        semantico_adicionar(token_atual.lexema, TOKEN_VALOR, token_atual.linha);
        proximo();
    }
    gerador_escrever(")");
    consumir(TOKEN_FECHA_PARENTESES, ")");
    bloco();
}

void comando() {
    if (token_atual.tipo == TOKEN_IDENTIFICADOR) {
        char n_id[100]; strcpy(n_id, token_atual.lexema);
        int lin = token_atual.linha;
        proximo();
        if (token_atual.tipo == TOKEN_ABRE_PARENTESES) { 
            semantico_validar_chamada(n_id, lin);
            gerador_escrever(n_id); gerador_escrever("("); proximo();
            while(token_atual.tipo != TOKEN_FECHA_PARENTESES) { gerador_escrever(token_atual.lexema); proximo(); }
            gerador_escrever(");\n    "); consumir(TOKEN_FECHA_PARENTESES, ")"); consumir(TOKEN_PONTO_VIRGULA, ";");
        } 
        else if (token_atual.tipo == TOKEN_ATRIBUICAO) {
            gerador_escrever(n_id); gerador_escrever(" = "); proximo();
            while(token_atual.tipo != TOKEN_PONTO_VIRGULA) {
                if (token_atual.tipo == TOKEN_IDENTIFICADOR) {
                    // Verifica se é chamada de função espiando o próximo caractere no buffer do arquivo
                    int c = fgetc(arquivo_global); ungetc(c, arquivo_global);
                    if (c == '(') semantico_validar_chamada(token_atual.lexema, token_atual.linha);
                }
                gerador_escrever(token_atual.lexema); proximo();
            }
            gerador_escrever(";\n    "); consumir(TOKEN_PONTO_VIRGULA, ";");
        }
    }
    else if (token_atual.tipo == TOKEN_INTEIRO || token_atual.tipo == TOKEN_REAL) {
        TipoToken t = token_atual.tipo; proximo();
        char var_nome[100]; strcpy(var_nome, token_atual.lexema);
        semantico_adicionar(var_nome, t, token_atual.linha);
        gerador_escrever(t == TOKEN_INTEIRO ? "int " : "float ");
        gerador_escrever(var_nome); proximo();
        if (token_atual.tipo == TOKEN_ATRIBUICAO) {
            gerador_escrever(" = "); proximo();
            if (token_atual.tipo == TOKEN_LER) {
                proximo(); consumir(TOKEN_ABRE_PARENTESES, "("); consumir(TOKEN_FECHA_PARENTESES, ")");
                gerador_escrever(t == TOKEN_INTEIRO ? "0; scanf(\"%d\", &" : "0.0; scanf(\"%f\", &");
                gerador_escrever(var_nome); gerador_escrever(")");
            } else {
                while(token_atual.tipo != TOKEN_PONTO_VIRGULA) { gerador_escrever(token_atual.lexema); proximo(); }
            }
        }
        gerador_escrever(";\n    "); consumir(TOKEN_PONTO_VIRGULA, ";");
    }
    else if (token_atual.tipo == TOKEN_RETORNE) {
        gerador_escrever("return "); proximo();
        while(token_atual.tipo != TOKEN_PONTO_VIRGULA) { gerador_escrever(token_atual.lexema); proximo(); }
        gerador_escrever(";\n    "); consumir(TOKEN_PONTO_VIRGULA, ";");
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
}

void bloco() {
    consumir(TOKEN_ABRE_CHAVE, "{"); gerador_escrever(" {\n    ");
    while (token_atual.tipo != TOKEN_FECHA_CHAVE && token_atual.tipo != TOKEN_FIM) comando();
    gerador_escrever("}\n\n"); consumir(TOKEN_FECHA_CHAVE, "}"); 
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
    P_LOG_INFO("V1.3: Analise concluida com Sucesso.");
}