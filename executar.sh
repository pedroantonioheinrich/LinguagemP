#!/bin/bash

# 1. Limpa e Compila o compilador da Linguagem P
make clean
make

# 2. Roda o compilador sobre o seu código fonte .lp
if [ -f "exemplos/teste_hardware.lp" ]; then
    ./lp_compilador exemplos/teste_hardware.lp
else
    echo "Erro: exemplos/teste_hardware.lp não encontrado."
    exit 1
fi

# 3. Compila o código C que foi gerado pelo seu compilador
if [ -f "codigo_gerado.c" ]; then
    gcc codigo_gerado.c -o programa_final
    echo "[SUCESSO] Código gerado compilado com GCC."
else
    echo "Erro: codigo_gerado.c não foi gerado."
    exit 1
fi

# 4. Executa o programa final
echo "[EXECUTANDO PROGRAMA FINAL...]"
./programa_final
echo -e "\n[PROGRAMA FINALIZADO COM SUCESSO]"