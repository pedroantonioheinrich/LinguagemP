#!/bin/bash

# Cores para o terminal
VERDE='\033[0;32m'
VERMELHO='\033[0;31m'
AZUL='\033[0;34m'
NC='\033[0m' # Sem cor

echo -e "${AZUL}🚀 Iniciando instalação da Linguagem P...${NC}"

# 1. Verificar se o GCC está instalado
echo -n "🔍 Verificando dependências: gcc... "
if ! command -v gcc &> /dev/null; then
    echo -e "${VERMELHO}ERRO${NC}"
    echo "--------------------------------------------------------"
    echo "❌ O compilador 'gcc' não foi encontrado no seu sistema."
    echo "A Linguagem P precisa do GCC para gerar os binários finais."
    echo "Como instalar:"
    echo "  No Ubuntu/Debian: sudo apt install build-essential"
    echo "  No MacOS: brew install gcc"
    echo "  No Fedora: sudo dnf install gcc"
    echo "--------------------------------------------------------"
    exit 1
else
    echo -e "${VERDE}OK!${NC}"
fi

# 2. Criar pastas necessárias para a compilação
mkdir -p obj
mkdir -p build

# 3. Compilar os módulos do tradutor
echo -e "${AZUL}📦 Compilando módulos do sistema...${NC}"
gcc -Wall -Wextra -g -Iinclude -c src/*.c
if [ $? -ne 0 ]; then
    echo -e "${VERMELHO}❌ Erro na compilação dos módulos. Verifique o código fonte.${NC}"
    exit 1
fi
mv *.o obj/

# 4. Gerar o executável principal (o compilador_p)
echo -e "${AZUL}🔧 Gerando binário da Linguagem P...${NC}"
gcc -o build/lp obj/*.o
if [ $? -ne 0 ]; then
    echo -e "${VERMELHO}❌ Erro ao gerar o executável final.${NC}"
    exit 1
fi

# 5. Mover para a pasta de binários do sistema
echo -e "${AZUL}📂 Configurando comando global...${NC}"
echo "A instalação requer permissão de administrador para criar o comando 'lp'."
sudo mv build/lp /usr/local/bin/lp

# 6. Limpeza
rm -rf obj build

echo "--------------------------------------------------------"
echo -e "${VERDE}✅ Instalação concluída com sucesso!${NC}"
echo -e "Agora você pode usar o comando ${AZUL}'lp'${NC} em qualquer terminal."
echo -e "Exemplo: ${AZUL}lp -r seu_arquivo.lp${NC}"
echo "--------------------------------------------------------"