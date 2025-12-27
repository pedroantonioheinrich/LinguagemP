#!/bin/bash
# desinstalar.sh - Remove a Linguagem P do sistema

VERMELHO='\033[0;31m'
VERDE='\033[0;32m'
NC='\033[0m'

echo -e "${VERMELHO}🗑️  Removendo a Linguagem P...${NC}"

# 1. Remover o binário global
if [ -f /usr/local/bin/lp ]; then
    echo "Excluindo /usr/local/bin/lp (requer sudo)..."
    sudo rm /usr/local/bin/lp
else
    echo "O comando 'lp' não foi encontrado em /usr/local/bin."
fi

# 2. Remover ficheiros temporários de instalações anteriores (se existirem)
if [ -d "$HOME/.linguagemp" ]; then
    echo "Limpando diretório de configuração local..."
    rm -rf "$HOME/.linguagemp"
fi

echo -e "${VERDE}✅ Desinstalação concluída!${NC}"