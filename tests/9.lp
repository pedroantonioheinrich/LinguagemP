funcao inteiro fatorial(inteiro n) {
    se (n <= 1) {
        retorne 1;
    }
    retorne n * fatorial(n - 1);
}

inicio() {
    inteiro num;
    exibir("Digite um numero para calcular o fatorial:");
    ler(num);
    
    inteiro res = fatorial(num);
    
    exibir("O fatorial e:");
    exibir(res);
}