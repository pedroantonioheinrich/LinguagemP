#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "lexico.h"

int linha_atual = 1;

Token criar_token(TipoToken tipo, const char* lexema) {
    Token t;
    t.tipo = tipo;
    t.linha = linha_atual;
    strncpy(t.lexema, lexema, 255);
    t.lexema[255] = '\0';
    return t;
}

Token proximo_token(FILE* arquivo) {
    int c;

    while ((c = fgetc(arquivo)) != EOF) {
        if (c == '\n') {
            linha_atual++;
            continue;
        }
        if (isspace(c)) continue;

        // Comentários (ignora até o fim da linha)
        if (c == '#') {
            while ((c = fgetc(arquivo)) != EOF && c != '\n');
            if (c == '\n') linha_atual++;
            continue;
        }
        
        // Suporte a comentários de linha dupla //
        if (c == '/') {
            int prox = fgetc(arquivo);
            if (prox == '/') {
                while ((c = fgetc(arquivo)) != EOF && c != '\n');
                if (c == '\n') linha_atual++;
                continue;
            }
            ungetc(prox, arquivo);
        }

        // Identificadores e Palavras-chave
        if (isalpha(c) || c == '_') {
            char lexema[256];
            int i = 0;
            lexema[i++] = (char)c;
            while (isalnum(c = fgetc(arquivo)) || c == '_') {
                if (i < 255) lexema[i++] = (char)c;
            }
            ungetc(c, arquivo);
            lexema[i] = '\0';

            // Mapeamento de Palavras-chave
            if (strcmp(lexema, "inicio") == 0) return criar_token(TOKEN_INICIO, lexema);
            if (strcmp(lexema, "inteiro") == 0) return criar_token(TOKEN_INTEIRO, lexema);
            if (strcmp(lexema, "real") == 0) return criar_token(TOKEN_REAL, lexema);
            if (strcmp(lexema, "cadeia") == 0) return criar_token(TOKEN_CADEIA, lexema);
            if (strcmp(lexema, "logico") == 0) return criar_token(TOKEN_LOGICO, lexema);
            
            // Suporte a 'vazio' e 'void' (Teste 59)
            if (strcmp(lexema, "vazio") == 0 || strcmp(lexema, "void") == 0) 
                return criar_token(TOKEN_VAZIO, lexema);
                
            if (strcmp(lexema, "se") == 0) return criar_token(TOKEN_SE, lexema);
            if (strcmp(lexema, "senao") == 0) return criar_token(TOKEN_SENAO, lexema);
            if (strcmp(lexema, "enquanto") == 0) return criar_token(TOKEN_ENQUANTO, lexema);
            
            // Suporte a 'sempre' (Teste 19) - Mapeado como ENQUANTO para facilitar tradução
            if (strcmp(lexema, "sempre") == 0) return criar_token(TOKEN_ENQUANTO, lexema);
            
            if (strcmp(lexema, "para") == 0) return criar_token(TOKEN_PARA, lexema);
            if (strcmp(lexema, "de") == 0) return criar_token(TOKEN_DE, lexema);
            if (strcmp(lexema, "ate") == 0) return criar_token(TOKEN_ATE, lexema);
            
            // Aceita 'retorne' e 'retorno' (Teste 40)
            if (strcmp(lexema, "retorne") == 0 || strcmp(lexema, "retorno") == 0) 
                return criar_token(TOKEN_RETORNO, lexema);
                
            if (strcmp(lexema, "funcao") == 0) return criar_token(TOKEN_FUNCAO, lexema);
            if (strcmp(lexema, "registro") == 0) return criar_token(TOKEN_REGISTRO, lexema);
            if (strcmp(lexema, "exibir") == 0) return criar_token(TOKEN_EXIBIR, lexema);
            if (strcmp(lexema, "ler") == 0) return criar_token(TOKEN_LER, lexema);
            if (strcmp(lexema, "verdadeiro") == 0) return criar_token(TOKEN_VERDADEIRO, lexema);
            if (strcmp(lexema, "falso") == 0) return criar_token(TOKEN_FALSO, lexema);
            if (strcmp(lexema, "e") == 0) return criar_token(TOKEN_E_LOGICO, lexema);
            if (strcmp(lexema, "ou") == 0) return criar_token(TOKEN_OU_LOGICO, lexema);
            if (strcmp(lexema, "nao") == 0) return criar_token(TOKEN_NAO_LOGICO, lexema);
            
            // Suporte a 'usar' para módulos (Teste 68)
            if (strcmp(lexema, "usar") == 0) return criar_token(TOKEN_IDENTIFICADOR, lexema);

            return criar_token(TOKEN_IDENTIFICADOR, lexema);
        }

        // Números (Inteiros e Reais)
        if (isdigit(c)) {
            char lexema[256];
            int i = 0;
            lexema[i++] = (char)c;
            int eh_real = 0;
            while (isdigit(c = fgetc(arquivo)) || c == '.') {
                if (c == '.') eh_real = 1;
                if (i < 255) lexema[i++] = (char)c;
            }
            ungetc(c, arquivo);
            lexema[i] = '\0';
            return criar_token(eh_real ? TOKEN_VALOR_REAL : TOKEN_VALOR_INTEIRO, lexema);
        }

        // Strings
        if (c == '"') {
            char lexema[256];
            int i = 0;
            while ((c = fgetc(arquivo)) != '"' && c != EOF) {
                if (i < 255) lexema[i++] = (char)c;
            }
            lexema[i] = '\0';
            return criar_token(TOKEN_VALOR_CADEIA, lexema);
        }

        // Operadores Compostos e Simples
        switch (c) {
            case '=':
                if ((c = fgetc(arquivo)) == '=') return criar_token(TOKEN_IGUAL_IGUAL, "==");
                ungetc(c, arquivo);
                return criar_token(TOKEN_ATRIBUICAO, "=");
            case '!':
                if ((c = fgetc(arquivo)) == '=') return criar_token(TOKEN_DIFERENTE, "!=");
                ungetc(c, arquivo);
                return criar_token(TOKEN_NAO_LOGICO, "!");
            case '<':
                if ((c = fgetc(arquivo)) == '=') return criar_token(TOKEN_MENOR_IGUAL, "<=");
                ungetc(c, arquivo);
                return criar_token(TOKEN_MENOR, "<");
            case '>':
                if ((c = fgetc(arquivo)) == '=') return criar_token(TOKEN_MAIOR_IGUAL, ">=");
                ungetc(c, arquivo);
                return criar_token(TOKEN_MAIOR, ">");
            case '+':
                if ((c = fgetc(arquivo)) == '+') return criar_token(TOKEN_MAIS_MAIS, "++");
                ungetc(c, arquivo);
                return criar_token(TOKEN_MAIS, "+");
            case '-':
                {
                    int prox = fgetc(arquivo);
                    if (prox == '>') return criar_token(TOKEN_SETA, "->");
                    if (prox == '-') return criar_token(TOKEN_MENOS_MENOS, "--");
                    ungetc(prox, arquivo);
                    return criar_token(TOKEN_MENOS, "-");
                }
            case '*': return criar_token(TOKEN_ASTERISCO, "*");
            case '/': return criar_token(TOKEN_BARRA, "/");
            case '%': return criar_token(TOKEN_PERCENTUAL, "%");
            case '.': return criar_token(TOKEN_PONTO, ".");
            case ',': return criar_token(TOKEN_VIRGULA, ",");
            case ';': return criar_token(TOKEN_PONTO_VIRGULA, ";");
            case '(': return criar_token(TOKEN_ABRE_PARENTESES, "(");
            case ')': return criar_token(TOKEN_FECHA_PARENTESES, ")");
            case '{': return criar_token(TOKEN_ABRE_CHAVE, "{");
            case '}': return criar_token(TOKEN_FECHA_CHAVE, "}");
            case '[': return criar_token(TOKEN_ABRE_COLCHETE, "[");
            case ']': return criar_token(TOKEN_FECHA_COLCHETE, "]");
            case '&': return criar_token(TOKEN_E_COMERCIAL, "&");
        }

        return criar_token(TOKEN_ERRO, "Caractere desconhecido");
    }

    return criar_token(TOKEN_EOF, "EOF");
}

const char* tipo_token_para_string(TipoToken tipo) {
    switch (tipo) {
        case TOKEN_INICIO: return "inicio";
        case TOKEN_INTEIRO: return "inteiro";
        case TOKEN_REAL: return "real";
        case TOKEN_CADEIA: return "cadeia";
        case TOKEN_LOGICO: return "logico";
        case TOKEN_VAZIO: return "vazio";
        case TOKEN_SE: return "se";
        case TOKEN_SENAO: return "senao";
        case TOKEN_ENQUANTO: return "enquanto";
        case TOKEN_PARA: return "para";
        case TOKEN_DE: return "de";
        case TOKEN_ATE: return "ate";
        case TOKEN_RETORNO: return "retorne";
        case TOKEN_FUNCAO: return "funcao";
        case TOKEN_REGISTRO: return "registro";
        case TOKEN_EXIBIR: return "exibir";
        case TOKEN_LER: return "ler";
        case TOKEN_VERDADEIRO: return "verdadeiro";
        case TOKEN_FALSO: return "falso";
        case TOKEN_IDENTIFICADOR: return "IDENTIFICADOR";
        case TOKEN_VALOR_INTEIRO: return "VALOR_INTEIRO";
        case TOKEN_VALOR_REAL: return "VALOR_REAL";
        case TOKEN_VALOR_CADEIA: return "VALOR_CADEIA";
        case TOKEN_IGUAL_IGUAL: return "==";
        case TOKEN_ATRIBUICAO: return "=";
        case TOKEN_MAIS_MAIS: return "++";
        case TOKEN_MENOS_MENOS: return "--";
        case TOKEN_PERCENTUAL: return "%";
        case TOKEN_EOF: return "EOF";
        default: return "DESCONHECIDO";
    }
}