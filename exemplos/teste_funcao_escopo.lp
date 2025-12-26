// ============================================================
// BATERIA DE TESTES: FUNÇÕES E ESCOPO (TEMA 3)
// ============================================================

// --- BLOCO 1: Funções Básicas e Retornos ---
funcao inteiro soma(inteiro a, inteiro b) {
    retorno a + b;
}

funcao real pi() {
    retorno 3.1415;
}

funcao vazio linha() {
    exibir("--------------------");
}

// --- BLOCO 2: Escopo e Sombreamento (Shadowing) ---
inteiro x; // Global

funcao vazio testar_escopo() {
    inteiro x; // Local (deve esconder a global)
    x = 50;
    exibir("Local x (deve ser 50):");
    exibir(x);
}

// --- BLOCO 3: Recursividade ---
funcao inteiro fatorial(inteiro n) {
    se (n <= 1) {
        retorno 1;
    }
    retorno n * fatorial(n - 1);
}

funcao inteiro fibonacci(inteiro n) {
    se (n <= 1) {
        retorno n;
    }
    retorno fibonacci(n - 1) + fibonacci(n - 2);
}

// --- BLOCO 4: Funções com Strings e Registros ---
registro Pessoa {
    cadeia nome;
    inteiro idade;
}

funcao vazio saudar(cadeia nome) {
    exibir("Ola ");
    exibir(nome);
}

// --- BLOCO 5: Funções que chamam Funções ---
funcao inteiro quadrado(inteiro n) {
    retorno n * n;
}

funcao inteiro soma_quadrados(inteiro a, inteiro b) {
    retorno quadrado(a) + quadrado(b);
}

// ============================================================
// EXECUÇÃO PRINCIPAL (INICIO)
// ============================================================
inicio() {
    // Testes 1-3: Aritmética e Funções
    exibir("T1 - Soma (10+5):");
    exibir(soma(10, 5));

    exibir("T2 - Real:");
    exibir(pi());

    linha();

    // Testes 4-5: Escopo
    x = 100; // Global
    testar_escopo();
    exibir("Global x (deve ser 100):");
    exibir(x);

    linha();

    // Testes 6-10: Recursividade
    exibir("T6 - Fatorial de 5 (120):");
    exibir(fatorial(5));

    exibir("T7 - Fibonacci de 6 (8):");
    exibir(fibonacci(6));

    linha();

    // Testes 11-15: Strings e Procedimentos
    saudar("Pedro");

    // Testes 16-20: Funções aninhadas
    exibir("T16 - Soma de Quadrados (3^2 + 4^2 = 25):");
    exibir(soma_quadrados(3, 4));

    // Testes 21-25: Escopo dentro de blocos (SE/ENQUANTO)
    inteiro i;
    i = 0;
    se (i == 0) {
        inteiro tmp; // Variável de escopo interno
        tmp = 999;
        exibir("Escopo interno SE:");
        exibir(tmp);
    }
    // Aqui o compilador limpou 'tmp' da tabela de símbolos via semantico_limpar_escopo

    // Testes 26-30: Expressões complexas em retornos
    exibir("T26 - Expressao em retorno (15):");
    exibir(soma(soma(2,3), soma(5,5)));
    
    exibir("FIM DOS TESTES TEMA 3");
}