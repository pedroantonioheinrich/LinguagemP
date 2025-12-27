
### 1. O Conteúdo do Arquivo: `FOLHA_DE_DICAS.md`

Este arquivo deve ser um resumo visual e prático de tudo o que a Linguagem P pode fazer.

```markdown
# 📜 Guia de Referência Rápida - Linguagem P

Este guia contém todos os comandos e estruturas válidas na Linguagem P.

## 🏗️ Estrutura Básica
Todo programa deve ter uma função de início.
```p
inicio() {
    // seu código aqui
}

```

## 📊 Variáveis e Tipos

* `inteiro`: Números inteiros (10, -5)
* `real`: Números decimais (3.14)
* `cadeia`: Textos ("Olá")
* `logico`: `verdadeiro` ou `falso`

## ⌨️ Entrada e Saída

* `exibir(valor)`: Imprime no console.
* `ler(variavel)`: Lê a entrada do usuário.

## 🔄 Controle de Fluxo

### Condicionais

```p
se (condicao) { } senao { }

```

### Laços (Loops)

```p
enquanto (condicao) { }

para (i de 1 ate 10) { }

sempre { 
    // loop infinito
}

```

## 📦 Estruturas (Registros)

```p
registro Pessoa {
    cadeia nome;
    inteiro idade;
}

```

## ⚙️ Funções

```p
funcao tipo_retorno nome(parametros) {
    retorne valor;
}

```

## 🔌 Comandos de Hardware/Sistema

* `esperar(ms)`: Pausa a execução.
* `ligar(pino)` / `desligar(pino)`: Controle de GPIO.
* `juntar(s1, s2)`: Concatena strings.
* `iguais(s1, s2)`: Compara strings.

```

---

### 2. Atualizando o `install-p.sh` para instalar a Documentação

Para que esse arquivo apareça na pasta do usuário, vamos modificar o instalador global. Ele criará uma pasta oculta chamada `.lp_docs` na home do usuário e colocará o guia lá.

Adicione este bloco ao seu `install-p.sh` antes da mensagem de sucesso:

```bash
# ... (código anterior de compilação e mv lp)

echo "📖 Instalando documentação local..."
DOC_DIR="$HOME/.linguagemp/docs"
mkdir -p "$DOC_DIR"

# Baixa a folha de dicas do seu GitHub
curl -sSL "$REPO_URL/FOLHA_DE_DICAS.md" -o "$DOC_DIR/FOLHA_DE_DICAS.md"

# Cria um comando de atalho para abrir a documentação rapidamente
echo "alias lp-docs='cat $DOC_DIR/FOLHA_DE_DICAS.md'" >> ~/.bashrc
echo "alias lp-docs='cat $DOC_DIR/FOLHA_DE_DICAS.md'" >> ~/.zshrc

echo "💡 Dica: Digite 'lp-docs' para ver a lista de comandos!"

```

---

### 3. Como o usuário usará isso?

Agora, a experiência do seu usuário no Japão será:

1. Ele roda o `curl ... | bash`.
2. A linguagem é instalada.
3. A qualquer momento, se ele esquecer como faz um `para` ou um `registro`, ele simplesmente digita no terminal:
```bash
lp-docs

```