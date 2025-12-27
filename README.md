---

# 📘 Linguagem P - Manual do Compilador e Especificação

A **Linguagem P** é uma linguagem de programação procedural, estaticamente tipada, desenvolvida para fins educacionais e de automação simples. Ela combina a clareza da sintaxe em português com a eficiência da compilação para código nativo C.

Este repositório contém o compilador completo, capaz de realizar análise léxica, sintática, semântica e geração de código otimizado.

---

## 🚀 1. Visão Geral e Arquitetura

O compilador da Linguagem P opera em um pipeline clássico de tradução:

1. **Análise Léxica (`lexico.c`):** Converte o código fonte em uma sequência de tokens (palavras-chave, identificadores, literais).
2. **Análise Sintática (`sintatico.c`):** Organiza os tokens em estruturas gramaticais (comandos, blocos, funções).
3. **Análise Semântica (`semantico.c`):** Valida o escopo de variáveis e a consistência dos tipos.
4. **Geração de Código (`gerador.c`):** Traduz a estrutura para um arquivo `.c` equivalente.
5. **Runtime de Suporte:** Uma camada de macros e funções pré-definidas para operações de hardware e strings.

---

## 🛠 2. Tipos de Dados e Variáveis

A Linguagem P suporta quatro tipos fundamentais e estruturas customizadas:

* `inteiro`: Números inteiros (ex: `10`, `-5`).
* `real`: Números de ponto flutuante (ex: `3.14`).
* `cadeia`: Sequências de caracteres (ex: `"Olá Mundo"`).
* `logico`: Valores booleanos (`verdadeiro` ou `falso`).

### Declaração e Inicialização

Você pode declarar variáveis de forma simples ou com atribuição imediata:

```p
inteiro idade = 25;
real saldo;
saldo = 150.50;
cadeia nome = "Pedro";

```

---

## 🏗 3. Estruturas de Dados (Registros)

Os **Registros** permitem criar tipos de dados complexos, equivalentes às `structs` da linguagem C.

```p
registro Usuario {
    inteiro id;
    cadeia nome;
    real saldo;
}

inicio() {
    Usuario p1;
    p1.id = 1;
    p1.nome = "Pedro";
    exibir(p1.nome);
}

```

---

## 🔄 4. Estruturas de Controle de Fluxo

### Condicionais

A linguagem utiliza a estrutura clássica `se-senao`.

```p
se (saldo > 100) {
    exibir("Saldo Rico");
} senao {
    exibir("Saldo Pobre");
}

```

### Laços de Repetição

Existem três formas principais de repetição:

1. **Enquanto:** Executa enquanto a condição for verdadeira.
2. **Para (Estilo C):** Controle total de inicialização, condição e incremento.
3. **Para (Simplificado):** Ideal para intervalos.
4. **Sempre:** Cria um loop infinito (equivalente a `while(1)`).

```p
// Para simplificado
para (i de 1 ate 10) {
    exibir(i);
}

// Loop sempre
sempre {
    exibir("Rodando...");
    esperar(1000);
}

```

---

## 📂 5. Modularização e Funções

As funções na Linguagem P suportam recursividade e retorno de todos os tipos básicos.

### Definição de Funções

```p
funcao inteiro fatorial(inteiro n) {
    se (n <= 1) {
        retorne 1;
    }
    retorne n * fatorial(n - 1);
}

```

### O Comando `usar`

Permite a organização do código em múltiplos arquivos. O compilador ignora a diretiva de inclusão de arquivos `.lp` para permitir que o programador gerencie os módulos na build.

```p
usar "utils.lp"

```

---

## 🧵 6. Manipulação de Strings

Como a linguagem alvo é C, a Linguagem P abstrai a complexidade de `strcmp` e `strcat` através de funções nativas integradas:

* `iguais(s1, s2)`: Retorna verdadeiro se as cadeias forem idênticas.
* `juntar(dest, src)`: Concatena a segunda string ao final da primeira.

---

## 🔌 7. Integração com Hardware (Modo Automação)

A Linguagem P foi projetada para suportar comandos simplificados para prototipagem:

* `ligar(pino)`: Ativa um sinal em um pino específico.
* `desligar(pino)`: Desativa o sinal.
* `esperar(ms)`: Pausa a execução por milissegundos específicos.

---

## 📋 8. Gramática Resumida (BNF)

```bnf
<programa>    ::= (<declaracao> | <funcao> | <registro> | <inicio>)*
<inicio>      ::= "inicio" "(" ")" <bloco>
<comando>     ::= <se> | <enquanto> | <para> | <atribuicao> | <exibir> | <retorno>
<expressao>   ::= <termo> ( ( "+" | "-" | "*" | "/" ) <termo> )*
<termo>       ::= <identificador> | <literal> | "(" <expressao> ")"

```

---

## ⚙️ 9. Compilação e Execução

Para compilar o projeto:

1. **Limpar builds anteriores:**
```bash
rm -rf obj compilador_p
mkdir obj

```


2. **Compilar o tradutor:**
```bash
gcc -Wall -Wextra -g -Iinclude -c src/*.c
mv *.o obj/
gcc -o compilador_p obj/*.o

```


3. **Gerar código C a partir de um arquivo `.lp`:**
```bash
./compilador_p arquivo.lp

```


4. **Compilar o código gerado:**
```bash
gcc codigo_gerado.c -o programa_final
./programa_final

```



---

## 🛠 10. Decisões de Implementação (FAQ)

**Por que compilar para C em vez de Assembly?**
C oferece uma camada de portabilidade e otimização de baixo nível que permite à Linguagem P rodar em diversas arquiteturas (x86, ARM, RISC-V) sem reescrever o gerador.

**Como funciona o tratamento de `retorno` e `retorne`?**
O analisador sintático foi ajustado para ser flexível. Ele identifica o token `TOKEN_RETORNO` mas também realiza uma comparação de lexema para aceitar a variante `retorne`, garantindo compatibilidade com diferentes estilos de escrita dos testes.

**Como o escopo é gerenciado?**
O `semantico.c` utiliza uma pilha de tabelas de símbolos. Ao entrar em um novo bloco `{`, um novo nível de escopo é criado, sendo destruído ao encontrar o `}` correspondente, garantindo que variáveis locais não vazem para o escopo global.

---

Este documento serve como a especificação oficial da versão 1.0 da Linguagem P.

---

## 🛠 Instalação

A Linguagem P pode ser instalada em sistemas Linux, macOS e Windows. Escolha o método mais adequado para você.

### 🌍 Instalação Automática (Linux e macOS)

Este é o método mais rápido para usuários em qualquer lugar do mundo. Ele baixa o script diretamente do GitHub e configura o comando `lp` automaticamente.

```bash
curl -fsSL https://raw.githubusercontent.com/pedroantonioheinrich/LinguagemP/refs/heads/main/install-p.sh | bash

```

### 🐧 Instalação Manual (Linux)

Se você já clonou o repositório, pode usar o instalador local:

1. Dê permissão de execução:
```bash
chmod +x instalar.sh

```


2. Execute o instalador:
```bash
./instalar.sh

```



### 🪟 Instalação no Windows

Para usuários Windows, utilize o script PowerShell:

1. Abra o PowerShell na pasta do projeto.
2. Caso os scripts estejam bloqueados, execute: `Set-ExecutionPolicy RemoteSigned -Scope CurrentUser`.
3. Execute o instalador:
```powershell
.\instalar.ps1

```


4. **Reinicie o terminal** para que o comando `lp` seja reconhecido.

---

## 🚀 Como Usar

Após a instalação, você terá o comando `lp` disponível globalmente.

### Compilar e Rodar Imediatamente

O modo mais simples de usar a Linguagem P é o modo de execução direta (`-r`). Ele traduz seu código, compila e executa, limpando os arquivos temporários automaticamente:

```bash
lp -r seu_arquivo.lp

```

### Apenas Traduzir para C

Se você deseja ver o código C gerado sem executá-lo:

```bash
lp -c seu_arquivo.lp

```

Isso gerará o arquivo `codigo_gerado.c` na sua pasta atual.

---

## 📝 Exemplo de Teste Rápido

Crie um arquivo chamado `teste.lp` e cole o código abaixo:

```p
inicio() {
    exibir("Ola mundo! A Linguagem P esta funcionando.");
}

```

Execute com:

```bash
lp -r teste.lp

```

---

