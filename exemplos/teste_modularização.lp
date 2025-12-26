funcao inteiro somar(inteiro x, inteiro y) {
    retorno x + y;
}

funcao vazio saudacao(cadeia nome) {
    exibir("Ola ");
    exibir(nome);
}

funcao inteiro fatorial(inteiro n) {
    se (n <= 1) {
        retorno 1;
    }
    retorno n * fatorial(n - 1);
}

inicio() {
    inteiro resultado;
    resultado = somar(10, 5);
    exibir(resultado);        // T1: 15

    saudacao("Pedro");        // T2: Ola Pedro

    inteiro fat;
    fat = fatorial(5);
    exibir(fat);              // T3: 120 (Recursividade)
}