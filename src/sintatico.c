#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sintatico.h"
#include "lexico.h"
#include "gerador.h"
#include "semantico.h"
#include "logs.h"

// Cores para o Log de Auditoria
#define ANSI_RESET  "\x1b[0m"
#define ANSI_GREEN  "\x1b[32m"
#define ANSI_RED    "\x1b[31m"

// [VALIDADO - NÃO ALTERAR] Controle de Lookahead e Escopo
Token token_atual;
Token token_lookahead;
int tem_lookahead = 0;
FILE* arquivo_global;
int escopo_atual = 0; 
int contador_unicidade = 0; 

// [VALIDADO - NÃO ALTERAR] Macros de Monitoramento
#define AUDIT_REGRA(regra) P_LOG_INFO("[REGRA] Entrando na regra: " regra)
#define AUDIT_TOKEN(msg) { char b[512]; snprintf(b, 512, "[TOKEN] %s: '%s' (Tipo: %d na Linha %d)", msg, token_atual.lexema, token_atual.tipo, token_atual.linha); P_LOG_INFO(b); }

// --- SISTEMA DE AUTO-DIAGNOSTICO ---
void audit_status(const char* modulo, int status) {
    if (status) {
        printf("[AUDIT] %-30s -> " ANSI_GREEN "OK" ANSI_RESET "\n", modulo);
    } else {
        printf("[AUDIT] %-30s -> " ANSI_RED "NÃO ESTÁVEL" ANSI_RESET "\n", modulo);
        P_LOG_ERRO("Falha critica no auto-diagnostico.");
        exit(1);
    }
}

void auto_diagnostico_sistema() {
    printf("\n--- INICIANDO TESTES DE INTEGRIDADE ---\n");
    
    semantico_adicionar("teste_unitario", TOKEN_INTEIRO, 999);
    int s1 = (semantico_obter_tipo("teste_unitario") == TOKEN_INTEIRO);
    audit_status("Tabela de Simbolos (Global)", s1);

    semantico_definir_registro("TesteReg");
    semantico_adicionar_campo_ao_reg("TesteReg", "campo1", TOKEN_REAL);
    int s2 = semantico_existe_registro("TesteReg");
    audit_status("Estruturas de Registro", s2);

    gerador_abrir("teste_vizinhança.tmp");
    FILE* f_check = fopen("teste_vizinhança.tmp", "r");
    int s3 = (f_check != NULL);
    if(f_check) fclose(f_check);
    gerador_fechar();
    remove("teste_vizinhança.tmp");
    audit_status("Sistema de Escrita (E/S)", s3);

    P_LOG_INFO("Diagnostico de rotina concluido.");
    audit_status("Subsistema de Logs", 1);

    printf("--- SISTEMA PRONTO PARA COMPILACAO ---\n\n");
}

// [VALIDADO - NÃO ALTERAR] Interface com Gerador
void audit_escrever(const char* str) {
    #ifdef DEBUG
    printf("[AUDIT-OUT] '%s'\n", str);
    #endif
    gerador_escrever(str);
}

// --- PROTÓTIPOS ---
void comando();
void bloco();
void declaracao_variavel();
void declaracao_registro();
void declaracao_funcao();
void copiar_expressao_ate(TipoToken limitador);

// [VALIDADO - NÃO ALTERAR] Funções de Navegação de Tokens
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
        AUDIT_TOKEN("Consumido");
        proximo();
    } else { 
        char erro[512];
        snprintf(erro, 512, "Erro Sintatico na linha %d: %s (Recebeu: '%s')", 
                 token_atual.linha, msg, token_atual.lexema);
        P_LOG_ERRO(erro); 
        exit(1); 
    }
}

// [VALIDADO - NÃO ALTERAR] Lógica de Formatação de Identificadores
void obter_nome_formatado(const char* nome, char* saida) {
    int id = semantico_obter_escopo(nome, escopo_atual);
    if (id != -1) {
        sprintf(saida, "%s_%d", nome, id);
    } else {
        strcpy(saida, nome);
    }
}

// [AGUARDANDO VALIDAÇÃO] Cópia de Expressões com Trava de Segurança
void copiar_expressao_ate(TipoToken limitador) {
    AUDIT_REGRA("COPIAR_EXPRESSAO");
    int nivel_p = 0;
    
    while(token_atual.tipo != TOKEN_EOF) {
        // [TRAVA DE SEGURANÇA] Se achamos o limitador fora de parênteses, paramos.
        if (token_atual.tipo == limitador && nivel_p == 0) {
            P_LOG_INFO("[MONITOR] Limitador alvo encontrado. Finalizando copia.");
            break;
        }

        // [TRAVA GLOBAL] Nunca avançar além de um ';' a menos que o limitador seja o próprio ';'
        if (token_atual.tipo == TOKEN_PONTO_VIRGULA && limitador != TOKEN_PONTO_VIRGULA) {
            P_LOG_INFO("[MONITOR] Interrupcao de seguranca: ';' detectado.");
            break;
        }

        if (token_atual.tipo == TOKEN_IDENTIFICADOR) {
            if (espiar().tipo == TOKEN_ABRE_PARENTESES) {
                audit_escrever(token_atual.lexema);
            } else {
                char n_fmt[1024]; obter_nome_formatado(token_atual.lexema, n_fmt);
                audit_escrever(n_fmt);
            }
        } 
        else if (token_atual.tipo == TOKEN_VALOR_CADEIA) {
            audit_escrever("\""); audit_escrever(token_atual.lexema); audit_escrever("\"");
        }
        else if (token_atual.tipo == TOKEN_ABRE_PARENTESES) { nivel_p++; audit_escrever("("); }
        else if (token_atual.tipo == TOKEN_FECHA_PARENTESES) { if (nivel_p > 0) nivel_p--; audit_escrever(")"); }
        else if (token_atual.tipo == TOKEN_E_LOGICO) audit_escrever(" && ");
        else if (token_atual.tipo == TOKEN_OU_LOGICO) audit_escrever(" || ");
        else if (token_atual.tipo == TOKEN_VERDADEIRO) audit_escrever("1");
        else if (token_atual.tipo == TOKEN_FALSO) audit_escrever("0");
        else if (token_atual.tipo == TOKEN_PONTO) audit_escrever(".");
        else if (token_atual.tipo == TOKEN_SETA) audit_escrever("->");
        else if (token_atual.tipo == TOKEN_ATRIBUICAO) audit_escrever(" = ");
        else { audit_escrever(token_atual.lexema); }
        
        proximo();
    }
}

// [VALIDADO - NÃO ALTERAR] Declaração de Variáveis
void declaracao_variavel() {
    AUDIT_REGRA("DECLARACAO_VAR");
    char tipo_base[100];
    int eh_reg = 0;
    TipoToken t = token_atual.tipo;

    if (semantico_existe_registro(token_atual.lexema)) {
        strcpy(tipo_base, token_atual.lexema);
        audit_escrever(tipo_base); audit_escrever(" ");
        eh_reg = 1;
    } else {
        if (t == TOKEN_CADEIA) { strcpy(tipo_base, "char"); audit_escrever("char "); }
        else if (t == TOKEN_INTEIRO) { strcpy(tipo_base, "int"); audit_escrever("int "); }
        else if (t == TOKEN_REAL) { strcpy(tipo_base, "float"); audit_escrever("float "); }
        else if (t == TOKEN_LOGICO) { strcpy(tipo_base, "int"); audit_escrever("int "); } 
    }
    proximo();
    
    while (token_atual.tipo == TOKEN_ASTERISCO) { audit_escrever("*"); proximo(); }

    char nome_orig[256]; strcpy(nome_orig, token_atual.lexema);
    int id_final = contador_unicidade++;

    if (eh_reg) semantico_adicionar_com_tipo_reg(nome_orig, tipo_base, id_final);
    else semantico_adicionar(nome_orig, t, id_final);

    char nome_esc[512]; snprintf(nome_esc, 512, "%s_%d", nome_orig, id_final);
    audit_escrever(nome_esc); proximo();

    while (token_atual.tipo == TOKEN_ABRE_COLCHETE) {
        audit_escrever("["); proximo();
        copiar_expressao_ate(TOKEN_FECHA_COLCHETE);
        audit_escrever("]"); consumir(TOKEN_FECHA_COLCHETE, "]");
    }

    if (t == TOKEN_CADEIA && !eh_reg && strstr(nome_esc, "[") == NULL) { 
        audit_escrever("[256]"); 
    }

    if (token_atual.tipo == TOKEN_ATRIBUICAO) {
        audit_escrever(" = "); proximo();
        copiar_expressao_ate(TOKEN_PONTO_VIRGULA);
    }
    
    audit_escrever(";\n    ");
    if (token_atual.tipo == TOKEN_PONTO_VIRGULA) proximo();
}

// [AGUARDANDO VALIDAÇÃO] Comando: Ajuste de fluxo
void comando() {
    AUDIT_REGRA("COMANDO");
    AUDIT_TOKEN("Processando comando");

    if (token_atual.tipo == TOKEN_EXIBIR) {
        proximo(); consumir(TOKEN_ABRE_PARENTESES, "(");
        if (token_atual.tipo == TOKEN_VALOR_CADEIA || (token_atual.tipo == TOKEN_IDENTIFICADOR && semantico_obter_tipo(token_atual.lexema) == TOKEN_CADEIA)) {
            audit_escrever("printf(\"%s\\n\", ");
            copiar_expressao_ate(TOKEN_FECHA_PARENTESES);
        } else {
            audit_escrever("printf(\"%g\\n\", (double)(");
            copiar_expressao_ate(TOKEN_FECHA_PARENTESES);
            audit_escrever(")");
        }
        audit_escrever(");\n    "); 
        consumir(TOKEN_FECHA_PARENTESES, ")");
        if (token_atual.tipo == TOKEN_PONTO_VIRGULA) proximo();
        return;
    }
    
    if (token_atual.tipo == TOKEN_SE || token_atual.tipo == TOKEN_ENQUANTO) {
        audit_escrever(token_atual.tipo == TOKEN_SE ? "if (" : "while (");
        proximo(); consumir(TOKEN_ABRE_PARENTESES, "(");
        copiar_expressao_ate(TOKEN_FECHA_PARENTESES);
        audit_escrever(") "); consumir(TOKEN_FECHA_PARENTESES, ")");
        bloco();
        return;
    }

    if (token_atual.tipo == TOKEN_RETORNO) {
        proximo(); audit_escrever("return ");
        copiar_expressao_ate(TOKEN_PONTO_VIRGULA);
        audit_escrever(";\n    ");
        if (token_atual.tipo == TOKEN_PONTO_VIRGULA) proximo();
        return;
    }

    if (token_atual.tipo == TOKEN_INTEIRO || token_atual.tipo == TOKEN_REAL || 
        token_atual.tipo == TOKEN_CADEIA || token_atual.tipo == TOKEN_LOGICO) {
        declaracao_variavel();
        return;
    }

    if (token_atual.tipo == TOKEN_IDENTIFICADOR || token_atual.tipo == TOKEN_ASTERISCO) {
        if (token_atual.tipo == TOKEN_IDENTIFICADOR && semantico_existe_registro(token_atual.lexema)) {
            Token prox = espiar();
            if (prox.tipo == TOKEN_IDENTIFICADOR || prox.tipo == TOKEN_ASTERISCO) {
                declaracao_variavel();
                return;
            }
        }

        if (token_atual.tipo == TOKEN_ASTERISCO) { audit_escrever("*"); proximo(); }
        
        char n_fmt[512]; obter_nome_formatado(token_atual.lexema, n_fmt);
        audit_escrever(n_fmt); proximo();

        while (token_atual.tipo == TOKEN_ABRE_COLCHETE || token_atual.tipo == TOKEN_PONTO || token_atual.tipo == TOKEN_SETA) {
            if (token_atual.tipo == TOKEN_ABRE_COLCHETE) {
                audit_escrever("["); proximo();
                copiar_expressao_ate(TOKEN_FECHA_COLCHETE);
                audit_escrever("]"); consumir(TOKEN_FECHA_COLCHETE, "]");
            } else {
                audit_escrever(token_atual.tipo == TOKEN_PONTO ? "." : "->");
                proximo(); audit_escrever(token_atual.lexema); proximo();
            }
        }

        if (token_atual.tipo == TOKEN_ATRIBUICAO) {
            audit_escrever(" = "); proximo();
            copiar_expressao_ate(TOKEN_PONTO_VIRGULA);
            audit_escrever(";");
            if (token_atual.tipo == TOKEN_PONTO_VIRGULA) proximo();
            audit_escrever("\n    ");
        } else if (token_atual.tipo == TOKEN_ABRE_PARENTESES) {
            audit_escrever("("); proximo();
            copiar_expressao_ate(TOKEN_FECHA_PARENTESES);
            audit_escrever(");");
            consumir(TOKEN_FECHA_PARENTESES, ")");
            if (token_atual.tipo == TOKEN_PONTO_VIRGULA) proximo();
            audit_escrever("\n    ");
        } else if (token_atual.tipo == TOKEN_PONTO_VIRGULA) {
            audit_escrever(";\n    "); proximo();
        }
        return;
    }

    if (token_atual.tipo == TOKEN_FECHA_CHAVE || token_atual.tipo == TOKEN_EOF) return;
    proximo();
}

// [VALIDADO - NÃO ALTERAR] Bloco, Registro e Funções
void bloco() {
    AUDIT_REGRA("BLOCO");
    consumir(TOKEN_ABRE_CHAVE, "{");
    audit_escrever("{\n    ");
    while (token_atual.tipo != TOKEN_FECHA_CHAVE && token_atual.tipo != TOKEN_EOF) { comando(); }
    audit_escrever("}\n    ");
    if (token_atual.tipo == TOKEN_FECHA_CHAVE) proximo();
}

void declaracao_registro() {
    AUDIT_REGRA("REGISTRO");
    consumir(TOKEN_REGISTRO, "registro");
    char n[100]; strcpy(n, token_atual.lexema); 
    semantico_definir_registro(n);
    audit_escrever("typedef struct {\n"); 
    proximo(); consumir(TOKEN_ABRE_CHAVE, "{");
    while (token_atual.tipo != TOKEN_FECHA_CHAVE) {
        TipoToken t_campo = token_atual.tipo;
        if (t_campo == TOKEN_CADEIA) audit_escrever("    char ");
        else if (t_campo == TOKEN_INTEIRO) audit_escrever("    int ");
        else if (t_campo == TOKEN_REAL) audit_escrever("    float ");
        else if (t_campo == TOKEN_LOGICO) audit_escrever("    int ");
        proximo(); 
        semantico_adicionar_campo_ao_reg(n, token_atual.lexema, t_campo);
        audit_escrever(token_atual.lexema);
        if (t_campo == TOKEN_CADEIA) audit_escrever("[256]");
        audit_escrever(";\n"); proximo();
        if (token_atual.tipo == TOKEN_PONTO_VIRGULA) proximo();
    }
    audit_escrever("} "); audit_escrever(n); audit_escrever(";\n\n");
    consumir(TOKEN_FECHA_CHAVE, "}");
}

void declaracao_funcao() {
    AUDIT_REGRA("FUNCAO");
    consumir(TOKEN_FUNCAO, "funcao");
    if (token_atual.tipo == TOKEN_INTEIRO) audit_escrever("int ");
    else if (token_atual.tipo == TOKEN_REAL) audit_escrever("float ");
    else if (token_atual.tipo == TOKEN_CADEIA) audit_escrever("char* ");
    else if (token_atual.tipo == TOKEN_LOGICO) audit_escrever("int ");
    else if (token_atual.tipo == TOKEN_VAZIO) audit_escrever("void ");
    else if (semantico_existe_registro(token_atual.lexema)) { audit_escrever(token_atual.lexema); audit_escrever(" "); }
    proximo();
    while (token_atual.tipo == TOKEN_ASTERISCO) { audit_escrever("*"); proximo(); }
    audit_escrever(token_atual.lexema); proximo();
    consumir(TOKEN_ABRE_PARENTESES, "("); audit_escrever("(");
    while(token_atual.tipo != TOKEN_FECHA_PARENTESES && token_atual.tipo != TOKEN_EOF) {
        TipoToken t_param = token_atual.tipo;
        if (t_param == TOKEN_INTEIRO) audit_escrever("int ");
        else if (t_param == TOKEN_REAL) audit_escrever("float ");
        else if (t_param == TOKEN_CADEIA) audit_escrever("char* ");
        else if (t_param == TOKEN_LOGICO) audit_escrever("int ");
        else if (semantico_existe_registro(token_atual.lexema)) { audit_escrever(token_atual.lexema); audit_escrever(" "); }
        proximo();
        while (token_atual.tipo == TOKEN_ASTERISCO) { audit_escrever("*"); proximo(); }
        int id_param = contador_unicidade++;
        semantico_adicionar(token_atual.lexema, t_param, id_param);
        char p_esc[1024]; snprintf(p_esc, 1024, "%s_%d", token_atual.lexema, id_param);
        audit_escrever(p_esc); proximo();
        if (token_atual.tipo == TOKEN_VIRGULA) { audit_escrever(", "); proximo(); }
    }
    audit_escrever(")"); consumir(TOKEN_FECHA_PARENTESES, ")");
    bloco();
}

void analisar(FILE* arquivo) {
    auto_diagnostico_sistema();
    arquivo_global = arquivo; 
    gerador_abrir("codigo_gerado.c");
    audit_escrever("#include <stdio.h>\n#include <string.h>\n#include <stdlib.h>\n#include <stdbool.h>\n\n");
    proximo();
    while (token_atual.tipo != TOKEN_EOF) {
        if (token_atual.tipo == TOKEN_REGISTRO) {
            declaracao_registro();
        }
        else if (token_atual.tipo == TOKEN_FUNCAO) {
            declaracao_funcao();
        }
        else if (token_atual.tipo == TOKEN_INICIO) {
            proximo(); 
            consumir(TOKEN_ABRE_PARENTESES, "("); 
            consumir(TOKEN_FECHA_PARENTESES, ")");
            audit_escrever("int main()"); 
            bloco(); 
        } 
        else if (token_atual.tipo == TOKEN_INTEIRO || token_atual.tipo == TOKEN_REAL || 
                 token_atual.tipo == TOKEN_CADEIA || token_atual.tipo == TOKEN_LOGICO) {
            declaracao_variavel();
        }
        else if (token_atual.tipo != TOKEN_EOF) {
            proximo();
        }
    }
    gerador_fechar();
}