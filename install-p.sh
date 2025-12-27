#!/bin/bash
# install-p.sh - Instalador Remoto da Linguagem P

# URL base corrigida para a raiz do repositório
REPO_URL="https://raw.githubusercontent.com/pedroantonioheinrich/LinguagemP/main"

echo "🌍 Baixando Linguagem P do repositório oficial..."

# Criar pasta temporária para compilação
mkdir -p temp_lp_install && cd temp_lp_install
mkdir -p src include

# 1. Baixar TODOS os arquivos .c necessários
echo "📥 Baixando módulos do tradutor..."
arquivos_c=(
    "principal.c" "lexico.c" "sintatico.c" "semantico.c" "gerador.c" 
    "logs.c" "formatador_c.c" "tradutor_string.c" "tradutor_expressao.c" 
    "tradutor_variavel.c" "tradutor_fluxo.c" "tradutor_registro.c" 
    "tradutor_funcao.c"
)

for file in "${arquivos_c[@]}"; do
    echo "  -> src/$file"
    curl -sSL "$REPO_URL/src/$file" -o "src/$file"
done

# 2. Baixar TODOS os arquivos .h necessários
echo "📥 Baixando cabeçalhos..."
arquivos_h=("lexico.h" "sintatico.h" "semantico.h" "gerador.h" "tradutores.h" "logs.h")

for file in "${arquivos_h[@]}"; do
    echo "  -> include/$file"
    curl -sSL "$REPO_URL/include/$file" -o "include/$file"
done

# 3. Verificar dependência do GCC
if ! command -v gcc &> /dev/null; then
    echo "❌ Erro: GCC não encontrado. Instale o build-essential primeiro."
    exit 1
fi

# 4. Compilar
echo "📦 Compilando binário..."
gcc -Iinclude -c src/*.c
gcc -o lp *.o

# 5. Instalar globalmente
echo "📂 Configurando comando 'lp' no sistema..."
sudo mv lp /usr/local/bin/lp

# Limpeza
cd .. && rm -rf temp_lp_install

echo "------------------------------------------------"
echo "✅ Linguagem P instalada com sucesso!"
echo "Teste agora com: lp -h"
echo "------------------------------------------------"