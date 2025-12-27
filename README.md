# 📘 Linguagem P - Manual do Compilador e Especificação

> **Criador e Desenvolvedor:** Pedro Antônio Heinrich  
> **Instagram:** [@streetegist](https://instagram.com/streetegist)

---

A **Linguagem P** é uma linguagem de programação procedural, estaticamente tipada, desenvolvida para fins educacionais e automação simples. Ela combina a clareza da sintaxe em português com a eficiência da compilação para código nativo C, permitindo rodar programas em diversas arquiteturas com alta performance.

Este repositório contém o compilador completo, capaz de realizar análise léxica, sintática, semântica e geração de código otimizado.

---

## 🌍 Instalação Global (Recomendado)

Para instalar a Linguagem P em qualquer lugar do mundo e configurar o comando `lp` automaticamente, utilize o instalador via terminal:

### Linux e macOS
```bash
curl -fsSL https://raw.githubusercontent.com/pedroantonioheinrich/LinguagemP/main/install-p.sh | bash

```

### Windows (PowerShell)

1. Certifique-se de ter o `gcc` (MinGW) instalado e no PATH.
2. Execute o script de instalação na pasta do projeto:

```powershell
.\instalar.ps1

```

*Nota: Pode ser necessário reiniciar o terminal após a instalação no Windows.*

---

## 🚀 Como Usar

Após a instalação, você terá o comando `lp` disponível globalmente.

### 1. Modo de Execução Direta (Estilo Interpretador)

Traduz seu código, compila e executa instantaneamente, limpando os arquivos temporários automaticamente:

```bash
lp -r seu_arquivo.lp

```

### 2. Apenas Traduzir para C

Se você deseja ver o código C gerado sem executá-lo:

```bash
lp -c seu_arquivo.lp

```

### 3. Guia de Comandos Rápido

Esqueceu a sintaxe? Acesse o manual diretamente no seu terminal:

```bash
lp-ajuda

```

---

## 🏗️ Recursos e Funcionalidades

A Linguagem P é robusta e validada por uma bateria de **76 testes automatizados**, suportando:

* **Tipagem Forte:** `inteiro`, `real`, `cadeia` e `logico`.
* **Vetores (Arrays):** Suporte total a listas de dados indexadas.
* **Operadores Lógicos:** Expressões complexas com `E`, `OU` e `NAO`.
* **Estruturas (Registros):** Criação de tipos de dados customizados (equivalente a `struct` em C).
* **Modularização:** Definição de funções com parâmetros, retorno e recursividade.
* **Hardware:** Comandos nativos para automação: `ligar(pino)`, `desligar(pino)` e `esperar(ms)`.

---

## 📂 Arquitetura do Compilador

O pipeline de tradução é dividido em módulos especializados:

1. **Análise Léxica (`lexico.c`):** Geração de tokens.
2. **Análise Sintática (`sintatico.c`):** Construção da gramática.
3. **Análise Semântica (`semantico.c`):** Validação de escopo e tipos.
4. **Tradutores (`tradutor_*.c`):** Módulos específicos para converter lógica P em sintaxe C.

---

## 🛠 Desenvolvimento Manual

Para compilar o próprio compilador a partir do código-fonte:

```bash
gcc -Wall -Wextra -g -Iinclude -c src/*.c
mkdir -p obj && mv *.o obj/
gcc -o lp obj/*.o

```

---

Este documento serve como a especificação oficial da versão 1.0 da Linguagem P.

Copyright (c) 2025 **Pedro Antônio Heinrich** ([@streetegist](https://www.google.com/url?sa=E&source=gmail&q=https://instagram.com/streetegist)).

```
