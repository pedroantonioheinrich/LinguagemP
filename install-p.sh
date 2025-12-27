#!/bin/bash
# install-p.sh - Instalador Remoto da Linguagem P

REPO_URL="https://raw.githubusercontent.com/pedroantonioheinrich/LinguagemP/refs/heads/main/install-p.sh"

echo "🌍 Baixando Linguagem P do repositório oficial..."

# Criar pasta temporária para compilação
mkdir -p temp_lp_install && cd temp_lp_install
mkdir -p src include obj

# Baixar os arquivos necessários (Exemplos de alguns arquivos)
# Você deve listar todos os seus arquivos .c e .h aqui
for file in principal.c sintatico.c lexico.c gerador.c semantico.c tradutor_expressao.c; do
    curl -sSL "$REPO_URL/src/$file" -o "src/$file"
done

for file in sintatico.h lexico.h gerador.h tradutores.h; do
    curl -sSL "$REPO_URL/include/$file" -o "include/$file"
done

# Compilar (Mesma lógica do seu instalar.sh anterior)
echo "📦 Compilando..."
gcc -Iinclude -c src/*.c
gcc -o lp *.o

# Instalar globalmente
echo "📂 Configurando comando 'lp'..."
sudo mv lp /usr/local/bin/lp

# Limpeza
cd .. && rm -rf temp_lp_install

echo "✅ Linguagem P instalada com sucesso!"