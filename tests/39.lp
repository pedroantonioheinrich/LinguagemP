// 1. Registro Global
registro Estudante {
    inteiro id;
    real nota;
}

// 2. Variáveis Globais
inteiro contador_global = 0;
Estudante lista[2];

// 3. Função Recursiva (Fibonacci)
funcao inteiro calcular_fib(inteiro n) {
    se (n <= 1) {
        retorne n;
    }
    retorne calcular_fib(n - 1) + calcular_fib(n - 2);
}

// 4. Função com Registro e Escopo
funcao real processar_estudante(real bonus) {
    inteiro contador_global = 100; // Shadowing: não deve afetar a global
    real media;
    
    exibir("--- Interno da Funcao ---");
    exibir("Shadowing contador (deve ser 100):");
    exibir(contador_global);
    
    media = (lista[0].nota + lista[1].nota) / 2;
    retorne media + bonus;
}

// 5. Bloco Principal
inicio() {
    exibir("=== TESTE FINAL SUPREMO DA LINGUAGEM P ===");

    // Testando Registros e Vetores Globais
    lista[0].id = 1;
    lista[0].nota = 7.5;
    lista[1].id = 2;
    lista[1].nota = 9.5;

    // Testando Shadowing e Escopo
    exibir("Media com bonus de 0.5 (deve ser 9.0):");
    exibir(processar_estudante(0.5));

    exibir("Contador Global (deve ser 0):");
    exibir(contador_global);

    // Testando Recursividade
    exibir("Fibonacci de 7 (deve ser 13):");
    exibir(calcular_fib(7));

    exibir("=== FIM DOS TESTES ===");
}