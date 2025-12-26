funcao inteiro fib(inteiro n) {
    se (n <= 1) {
        retorne n;
    }
    retorne fib(n - 1) + fib(n - 2);
}

inicio() {
    exibir("Fibonacci de 6 (deve ser 8):");
    exibir(fib(6));
}