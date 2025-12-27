# 📕 GUIA DE COMANDOS - LINGUAGEM P

## 🔹 Variáveis
inteiro a = 10;
real b = 5.5;
cadeia c = "texto";
logico d = verdadeiro;

## 🔹 Controle
se (condicao) { ... } senao { ... }
enquanto (condicao) { ... }
para (i de 1 ate 10) { ... }
sempre { ... }

## 🔹 Funções e Registros
registro Item { cadeia nome; real preco; }
funcao inteiro soma(inteiro x) { retorne x + 1; }

## 🔹 Hardware e Sistema
esperar(1000); // Milissegundos
exibir("Olá");
ler(variavel);

## 🚀 Combinações Avançadas (O que você pode criar)

### 🔄 Recursividade
Você pode criar funções que chamam a si mesmas:
```p
funcao inteiro fatorial(inteiro n) {
    se (n <= 1) { retorne 1; }
    retorne n * fatorial(n - 1);
}

📋 Manipulação de Strings
Use as funções nativas para lógica de texto:

Snippet de código

se (iguais(senha, "1234")) {
    exibir("Acesso Permitido");
}

🤖 Automação de Hardware
Combine sempre com controle de pino:

Snippet de código

sempre {
    ligar(13);
    esperar(500);
    desligar(13);
    esperar(500);
}

