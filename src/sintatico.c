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
int escopo_atual = 0; 

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

/**
 * Funcao auxiliar para copiar expressoes colando operadores compostos (>=, <=, ==)
 */
void copiar_expressao_ate(TipoToken limitador) {
    int nivel_p = 0;
    while(token_atual.tipo != TOKEN_FIM) {
        if (token_atual.tipo == limitador && nivel_p == 0) break;
        
        if (token_atual.tipo == TOKEN_E) gerador_escrever(" && ");
        else if (token_atual.tipo == TOKEN_OU) gerador_escrever(" || ");
        else if (token_atual.tipo == TOKEN_NAO) gerador_escrever(" ! ");
        else if (token_atual.tipo == TOKEN_ABRE_PARENTESES) { nivel_p++; gerador_escrever("("); }
        else if (token_atual.tipo == TOKEN_FECHA_PARENTESES) { nivel_p--; gerador_escrever(")"); }
        else if (token_atual.tipo == TOKEN_IGUAL) {
            gerador_escrever(" == "); // Garante que == nao tenha espaco interno
        }
        else if (token_atual.tipo == TOKEN_OPERADOR || token_atual.tipo == TOKEN_ATRIBUICAO) {
            // Se for > ou < ou = e o proximo for =, colamos
            if (strcmp(token_atual.lexema, ">") == 0 || strcmp(token_atual.lexema, "<") == 0 || strcmp(token_atual.lexema, "=") == 0) {
                char op[10]; strcpy(op, token_atual.lexema);
                proximo();
                if (token_atual.tipo == TOKEN_ATRIBUICAO || token_atual.tipo == TOKEN_IGUAL) {
                    gerador_escrever(" "); gerador_escrever(op); gerador_escrever("= ");
                } else {
                    gerador_escrever(" "); gerador_escrever(op); gerador_escrever(" ");
                    continue; // Ja avancamos o token
                }
            } else {
                gerador_escrever(" "); gerador_escrever(token_atual.lexema); gerador_escrever(" ");
            }
        }
        else {
            // Nao colocar espaco antes de colchetes ou pontos
            if (token_atual.tipo != TOKEN_ABRE_COLCHETE && strcmp(token_atual.lexema, ".") != 0) {
                gerador_escrever(" ");
            }
            gerador_escrever(token_atual.lexema);
        }
        proximo();
    }
}

void declaracao_variavel() {
    TipoToken t = token_atual.tipo;
    if (t == TOKEN_IDENTIFICADOR) {
        char tipo_reg[100]; strcpy(tipo_reg, token_atual.lexema);
        gerador_escrever(tipo_reg); gerador_escrever(" "); proximo();
        char nome_var[100]; strcpy(nome_var, token_atual.lexema);
        semantico_adicionar_com_tipo_reg(nome_var, tipo_reg, escopo_atual);
        gerador_escrever(nome_var); proximo();
    } else {
        if (t == TOKEN_CADEIA) {
            gerador_escrever("char "); proximo();
            char nome_var[100]; strcpy(nome_var, token_atual.lexema);
            semantico_adicionar(nome_var, TOKEN_CADEIA, escopo_atual);
            gerador_escrever(nome_var); gerador_escrever("[256]"); proximo();
        } else {
            gerador_escrever(t == TOKEN_INTEIRO ? "int " : "float "); proximo();
            char nome_var[100]; strcpy(nome_var, token_atual.lexema);
            semantico_adicionar(nome_var, t, escopo_atual);
            gerador_escrever(nome_var); proximo();
        }
    }
    if (token_atual.tipo == TOKEN_ABRE_COLCHETE) {
        gerador_escrever("["); proximo(); gerador_escrever(token_atual.lexema); proximo();
        consumir(TOKEN_FECHA_COLCHETE, "]"); gerador_escrever("]");
    }
    if (token_atual.tipo == TOKEN_ATRIBUICAO) {
        gerador_escrever(" = "); proximo(); copiar_expressao_ate(TOKEN_PONTO_VIRGULA);
    }
    gerador_escrever(";\n    "); consumir(TOKEN_PONTO_VIRGULA, ";");
}

void comando() {
    if (token_atual.tipo == TOKEN_RETORNE) {
        proximo(); gerador_escrever("return ");
        copiar_expressao_ate(TOKEN_PONTO_VIRGULA);
        gerador_escrever(";\n    "); consumir(TOKEN_PONTO_VIRGULA, ";");
    }
    else if (token_atual.tipo == TOKEN_INTEIRO || token_atual.tipo == TOKEN_REAL || token_atual.tipo == TOKEN_CADEIA) {
        declaracao_variavel();
    }
    else if (token_atual.tipo == TOKEN_PARA) {
        proximo(); consumir(TOKEN_ABRE_PARENTESES, "("); gerador_escrever("for (");
        char var_nome[100]; strcpy(var_nome, token_atual.lexema);
        gerador_escrever(var_nome); proximo();
        consumir(TOKEN_ATRIBUICAO, "="); gerador_escrever(" = ");
        copiar_expressao_ate(TOKEN_PONTO_VIRGULA);
        gerador_escrever(";"); consumir(TOKEN_PONTO_VIRGULA, ";");
        copiar_expressao_ate(TOKEN_PONTO_VIRGULA);
        gerador_escrever(";"); consumir(TOKEN_PONTO_VIRGULA, ";");
        char var_inc[100]; strcpy(var_inc, token_atual.lexema);
        gerador_escrever(var_inc); proximo();
        consumir(TOKEN_ATRIBUICAO, "="); gerador_escrever(" = ");
        copiar_expressao_ate(TOKEN_FECHA_PARENTESES);
        gerador_escrever(") "); consumir(TOKEN_FECHA_PARENTESES, ")");
        bloco(); gerador_escrever("\n    ");
    }
    else if (token_atual.tipo == TOKEN_SE || token_atual.tipo == TOKEN_ENQUANTO) {
        TipoToken tipo = token_atual.tipo;
        proximo(); consumir(TOKEN_ABRE_PARENTESES, "(");
        gerador_escrever(tipo == TOKEN_SE ? "if (" : "while (");
        copiar_expressao_ate(TOKEN_FECHA_PARENTESES);
        gerador_escrever(") "); consumir(TOKEN_FECHA_PARENTESES, ")");
        bloco();
        if (tipo == TOKEN_SE && token_atual.tipo == TOKEN_SENAO) {
            gerador_escrever(" else "); proximo();
            if (token_atual.tipo == TOKEN_SE) comando();
            else bloco();
        }
        gerador_escrever("\n    ");
    }
    else if (token_atual.tipo == TOKEN_IDENTIFICADOR) {
        TipoToken tipo_id = semantico_obter_tipo(token_atual.lexema);
        if (tipo_id == TOKEN_ERRO && escopo_atual > 0) { 
            declaracao_variavel();
        } else {
            char n1[100]; strcpy(n1, token_atual.lexema); proximo();
            gerador_escrever(n1);
            while (token_atual.tipo == TOKEN_ABRE_COLCHETE || 
                  (token_atual.tipo == TOKEN_OPERADOR && strcmp(token_atual.lexema, ".") == 0) || 
                   token_atual.tipo == TOKEN_ABRE_PARENTESES) {
                if (token_atual.tipo == TOKEN_ABRE_COLCHETE) {
                    gerador_escrever("["); proximo(); copiar_expressao_ate(TOKEN_FECHA_COLCHETE);
                    gerador_escrever("]"); proximo();
                } else if (token_atual.tipo == TOKEN_ABRE_PARENTESES) {
                    gerador_escrever("("); proximo(); copiar_expressao_ate(TOKEN_FECHA_PARENTESES);
                    gerador_escrever(")"); proximo();
                } else {
                    gerador_escrever("."); proximo(); gerador_escrever(token_atual.lexema); proximo();
                }
            }
            if (token_atual.tipo == TOKEN_ATRIBUICAO) {
                gerador_escrever(" = "); proximo(); copiar_expressao_ate(TOKEN_PONTO_VIRGULA);
            }
            gerador_escrever(";\n    "); consumir(TOKEN_PONTO_VIRGULA, ";");
        }
    }
    else if (token_atual.tipo == TOKEN_EXIBIR || token_atual.tipo == TOKEN_LER) {
        TipoToken t = token_atual.tipo;
        proximo(); consumir(TOKEN_ABRE_PARENTESES, "(");
        if (t == TOKEN_EXIBIR) {
            // Se o lexema comeca com aspas ou o tipo for numero (constante) mas o semantico diz ser cadeia
            if (token_atual.lexema[0] == '"') {
                gerador_escrever("printf(\"%s\\n\", "); 
                gerador_escrever(token_atual.lexema); 
                gerador_escrever(")"); proximo();
            } else {
                TipoToken tipo_var = semantico_obter_tipo(token_atual.lexema);
                if (tipo_var == TOKEN_CADEIA) {
                    gerador_escrever("printf(\"%s\\n\", "); gerador_escrever(token_atual.lexema); gerador_escrever(")");
                    proximo();
                } else {
                    gerador_escrever("printf(\"%g\\n\", (double)("); copiar_expressao_ate(TOKEN_FECHA_PARENTESES); gerador_escrever("))");
                }
            }
        } else {
            char var_nome[100]; strcpy(var_nome, token_atual.lexema);
            TipoToken tipo_var = semantico_obter_tipo(var_nome);
            if (tipo_var == TOKEN_CADEIA) {
                gerador_escrever("fgets("); gerador_escrever(var_nome);
                gerador_escrever(", 256, stdin); ");
                gerador_escrever(var_nome); 
                gerador_escrever("[strcspn("); gerador_escrever(var_nome); 
                gerador_escrever(", \"\\n\")] = 0");
            } else {
                gerador_escrever(tipo_var == TOKEN_INTEIRO ? "scanf(\"%d\", &" : "scanf(\"%f\", &");
                gerador_escrever(var_nome);
                while(token_atual.tipo == TOKEN_OPERADOR && strcmp(token_atual.lexema, ".") == 0) {
                    gerador_escrever("."); proximo(); gerador_escrever(token_atual.lexema);
                }
                gerador_escrever("); getchar()"); 
            }
            proximo();
        }
        consumir(TOKEN_FECHA_PARENTESES, ")"); gerador_escrever(";\n    "); consumir(TOKEN_PONTO_VIRGULA, ";");
    }
}

void declaracao_funcao() {
    escopo_atual = 1;
    consumir(TOKEN_FUNCAO, "funcao");
    TipoToken tr = token_atual.tipo;
    if (tr == TOKEN_INTEIRO || tr == TOKEN_REAL || tr == TOKEN_CADEIA) {
        gerador_escrever(tr == TOKEN_INTEIRO ? "int " : (tr == TOKEN_REAL ? "float " : "char* "));
        proximo();
    } else { gerador_escrever("void "); }
    char nome_fun[100]; strcpy(nome_fun, token_atual.lexema);
    gerador_escrever(nome_fun); proximo();
    consumir(TOKEN_ABRE_PARENTESES, "("); gerador_escrever("(");
    while (token_atual.tipo != TOKEN_FECHA_PARENTESES) {
        TipoToken tp = token_atual.tipo;
        gerador_escrever(tp == TOKEN_INTEIRO ? "int " : (tp == TOKEN_REAL ? "float " : "char* "));
        proximo();
        gerador_escrever(token_atual.lexema);
        semantico_adicionar(token_atual.lexema, tp, escopo_atual);
        proximo();
        if (token_atual.tipo == TOKEN_VIRGULA) { gerador_escrever(", "); proximo(); }
    }
    consumir(TOKEN_FECHA_PARENTESES, ")"); gerador_escrever(")");
    bloco();
    gerador_escrever("\n\n");
    semantico_limpar_escopo_local();
    escopo_atual = 0;
}

void declaracao_registro() {
    consumir(TOKEN_REGISTRO, "registro");
    char nome_reg[100]; strcpy(nome_reg, token_atual.lexema);
    semantico_definir_registro(nome_reg);
    proximo(); 
    gerador_escrever("typedef struct {\n");
    consumir(TOKEN_ABRE_CHAVE, "{");
    while (token_atual.tipo != TOKEN_FECHA_CHAVE) {
        if (token_atual.tipo == TOKEN_INTEIRO || token_atual.tipo == TOKEN_REAL || token_atual.tipo == TOKEN_CADEIA) {
            TipoToken tipo_campo = token_atual.tipo;
            gerador_escrever("    ");
            if (tipo_campo == TOKEN_CADEIA) {
                proximo(); gerador_escrever("char "); gerador_escrever(token_atual.lexema); gerador_escrever("[256];\n");
            } else {
                gerador_escrever(tipo_campo == TOKEN_INTEIRO ? "int " : "float ");
                proximo(); gerador_escrever(token_atual.lexema); gerador_escrever(";\n");
            }
            semantico_adicionar_campo_ao_reg(nome_reg, token_atual.lexema, tipo_campo);
            proximo(); consumir(TOKEN_PONTO_VIRGULA, ";");
        } else proximo();
    }
    consumir(TOKEN_FECHA_CHAVE, "}");
    gerador_escrever("} "); gerador_escrever(nome_reg); gerador_escrever(";\n\n");
}

void bloco() {
    consumir(TOKEN_ABRE_CHAVE, "{"); gerador_escrever(" {\n    ");
    while (token_atual.tipo != TOKEN_FECHA_CHAVE && token_atual.tipo != TOKEN_FIM) comando();
    gerador_escrever("}\n    "); consumir(TOKEN_FECHA_CHAVE, "}"); 
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
            gerador_escrever("int main() "); bloco();
            semantico_limpar_escopo_local();
            escopo_atual = 0;
        } 
        else if (token_atual.tipo == TOKEN_INTEIRO || token_atual.tipo == TOKEN_REAL || token_atual.tipo == TOKEN_CADEIA || token_atual.tipo == TOKEN_IDENTIFICADOR) {
            escopo_atual = 0; 
            declaracao_variavel();
        }
        else proximo();
    }
    gerador_fechar();
    P_LOG_INFO("V11.2: Ajustes de comparadores e printf concluidos.");
}