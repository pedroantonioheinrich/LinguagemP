funcao inteiro fibonacci(inteiro n) {
    se (n <= 1) {
        retorne n;
    }
    retorne fibonacci(n - 1) + fibonacci(n - 2);
}

inicio() {
    exibir("--- Sequencia Fibonacci ---");
    inteiro resultado = fibonacci(10);
    exibir("O 10o termo eh:");
    exibir(resultado); 
    // O resultado deve ser 55
}