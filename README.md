
```markdown
# 🚀 Linguagem P - Compilador de Alto Nível para Simulação de Hardware

A **Linguagem P** é uma linguagem de programação procedural e imperativa, desenvolvida para simplificar a programação de sistemas embarcados e simulação de hardware. Ela abstrai a complexidade do C puro, oferecendo uma sintaxe amigável em português, enquanto mantém a performance através de uma tradução direta para código nativo.

CRIADA POR PEDRO ANTÔNIO HEINRICH NETO
---

## 🏗️ 1. Arquitetura do Compilador

O projeto segue o modelo clássico de compiladores de passo único (single-pass), dividido em quatro camadas principais que trabalham em pipeline:

### A. Analisador Léxico (`src/lexico.c` / `src/lexico.h`)
O "Scanner". Ele lê o arquivo fonte `.lp` caractere por caractere e os agrupa em **Tokens**.
- **Comentários:** Ignora automaticamente qualquer texto após `//`.
- **Palavras-Chave:** Reconhece comandos como `inicio`, `inteiro`, `constante`, `ligar`, `esperar`, etc.
- **Operadores:** Identifica símbolos matemáticos, incluindo o operador de resto `%` e comparadores relacionais (`==`, `<=`, etc).
- **Tratamento de Strings:** Captura cadeias de caracteres entre aspas duplas para o comando `exibir`.



### B. Analisador Sintático (`src/sintatico.c`)
O "Coração". Ele recebe os tokens e verifica se a ordem das frases respeita as regras gramaticais da Linguagem P.
- **Recursive Descent Parser:** Utiliza funções recursivas para processar blocos `{}` e comandos.
- **Sincronização:** Garante que cada comando termine com `;` e que parênteses sejam fechados corretamente.
- **Tradução On-the-fly:** À medida que valida a gramática, ele já aciona o Gerador de Código.

### C. Analisador Semântico (`src/semantico.c`)
O "Cérebro". Ele cuida do significado e das regras de negócio da linguagem.
- **Tabela de Símbolos:** Armazena o nome e o tipo de cada variável declarada.
- **Proteção de Constantes:** Impede que uma variável declarada como `constante` receba uma nova atribuição (`TOKEN_ATRIBUICAO`) durante o tempo de compilação, emitindo um erro fatal caso o usuário tente alterá-la.

### D. Gerador de Código (`src/gerador.c`)
O "Tradutor". Ele converte as estruturas da Linguagem P para a sintaxe da linguagem C (ISO C99).
- Adiciona automaticamente os headers necessários (`stdio.h`, `unistd.h`, `stdbool.h`).
- Converte o comando `esperar(ms)` para a função `usleep(ms * 1000)` do POSIX.
- Mapeia os comandos `ligar` e `desligar` para saídas formatadas no console que simulam a ativação de pinos de hardware.

---

## 🛠️ 2. Especificação da Linguagem

### Tipos de Dados
- `inteiro`: Números inteiros de 32 bits.
- `real`: Números de ponto flutuante.
- `constante`: Modificador que torna uma variável imutável após a inicialização.

### Estruturas de Controle
- `se (condicao) { ... } senao { ... }`: Desvio condicional.
- `enquanto (condicao) { ... }`: Laço de repetição baseado em predicado.

### Comandos de Hardware (Simulados)
- `ligar(pino)`: Simula a aplicação de sinal HIGH (3.3v/5v) em um GPIO.
- `desligar(pino)`: Simula sinal LOW (0v).
- `esperar(tempo_ms)`: Pausa a execução do programa pelo tempo especificado em milissegundos.



---

## 🚀 3. Como Compilar e Executar

O projeto utiliza um `Makefile` para automatizar o processo de build.

### Pré-requisitos
- Compilador `gcc` (GNU Compiler Collection).
- Ferramenta `make`.

### Comandos
1. **Compilar o Compilador:**
   ```bash
   make

```

Isso gerará o executável `lp_compilador`.

2. **Compilar e Rodar um Script P:**
```bash
./lp_compilador exemplos/meu_codigo.lp

```


Este comando gera o arquivo `codigo_gerado.c`, que é automaticamente compilado pelo `make run` para gerar o binário final `meu_programa_p`.

---

## 📈 4. Exemplo de Código (`super_teste.lp`)

Excelente ideia, Pedro. Adicionar a **Especificação Gramatical (BNF)** eleva o nível do seu projeto, transformando-o de um simples script em uma linguagem formalmente definida.

Aqui está o seu arquivo `README.md` completo e atualizado, integrando a gramática como o novo tópico 6.

---

### 📄 Arquivo: `README.md` (Versão Final com Gramática BNF)

```markdown
# 🚀 Linguagem P - Compilador de Alto Nível para Simulação de Hardware

A **Linguagem P** é uma linguagem de programação procedural e imperativa, desenvolvida para simplificar a programação de sistemas embarcados e simulação de hardware. Ela abstrai a complexidade do C puro, oferecendo uma sintaxe amigável em português, enquanto mantém a performance através de uma tradução direta para código nativo.

---

## 🏗️ 1. Arquitetura do Compilador

O projeto segue o modelo clássico de compiladores de passo único (single-pass), dividido em quatro camadas principais que trabalham em pipeline:

### A. Analisador Léxico (`src/lexico.c`)
O "Scanner". Ele lê o arquivo fonte `.lp` caractere por caractere e os agrupa em **Tokens**.
- **Comentários:** Ignora automaticamente qualquer texto após `//`.
- **Operadores:** Identifica símbolos matemáticos, incluindo o operador de resto `%`.

### B. Analisador Sintático (`src/sintatico.c`)
O "Coração". Utiliza um algoritmo de **Recursive Descent Parser** para validar a gramática e acionar o gerador de código.

### C. Analisador Semântico (`src/semantico.c`)
O "Cérebro". Gerencia a **Tabela de Símbolos** e garante a **Proteção de Constantes**, impedindo que valores marcados como `constante` sejam alterados.

### D. Gerador de Código (`src/gerador.c`)
O "Tradutor". Converte as estruturas da Linguagem P para a sintaxe da linguagem C (ISO C99), incluindo headers como `unistd.h` para suporte ao comando `esperar`.



---

## 🛠️ 2. Especificação da Linguagem

### Tipos de Dados
- `inteiro`: Números inteiros.
- `real`: Números de ponto flutuante.
- `constante`: Modificador de imutabilidade.

### Comandos de Hardware
- `ligar(pino)` / `desligar(pino)`: Simula sinais digitais.
- `esperar(ms)`: Pausa a execução em milissegundos.

---

## 📜 6. Gramática Formal (BNF)

Abaixo está a definição formal da sintaxe da Linguagem P em Backus-Naur Form. Esta gramática define a hierarquia de precedência e a estrutura de todos os comandos suportados.

```bnf
<programa>         ::= "inicio" "(" ")" <bloco>

<bloco>            ::= "{" <lista_comandos> "}"

<lista_comandos>   ::= <comando> <lista_comandos> | ε

<comando>          ::= <declaracao> ";"
                     | <atribuicao> ";"
                     | <atribuicao_composta> ";"
                     | <comando_se>
                     | <comando_enquanto>
                     | <comando_para>
                     | <comando_exibir> ";"
                     | <comando_hardware> ";"

<atribuicao_composta> ::= <id> "+=" <expressao>
                        | <id> "-=" <expressao>

<comando_para>     ::= "para" "(" [<declaracao_simples> | <atribuicao>] ";" <expressao_logica> ";" <atribuicao> ")" <bloco>

<declaracao>       ::= "inteiro" <id> [ "=" <expressao> ]
                     | "real" <id> [ "=" <expressao> ]
                     | "constante" <tipo_base> <id> "=" <expressao>

<tipo_base>        ::= "inteiro" | "real"

<atribuicao>       ::= <id> "=" <expressao>

<comando_se>       ::= "se" "(" <expressao_logica> ")" <bloco> [ "senao" <bloco> ]

<comando_enquanto> ::= "enquanto" "(" <expressao_logica> ")" <bloco>

<expressao_logica> ::= <expressao> <op_relacional> <expressao>

<expressao>        ::= <termo> { <op_aditivo> <termo> }

<termo>            ::= <fator> { <op_multiplicativo> <fator> }

<op_multiplicativo> ::= "*" | "/" | "%"

<id>               ::= [a-zA-Z_][a-zA-Z0-9_]*
<numero>           ::= [0-9]+ [ "." [0-9]+ ]

```

---

## 🚀 3. Como Compilar e Executar

1. **Build do Compilador:**
```bash
make clean && make

```


2. **Compilação do Script .lp:**
```bash
./lp_compilador exemplos/super_teste.lp

```


3. **Execução do Programa:**
```bash
./meu_programa_p

```



---

## 📂 5. Organização de Arquivos

* `src/`: Código-fonte do compilador.
* `exemplos/`: Scripts de teste.
* `Makefile`: Automação de build.

```

---

```