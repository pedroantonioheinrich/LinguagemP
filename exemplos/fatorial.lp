funcao inteiro fatorial(inteiro n) {
    se (n == 0) {
        retorne 1;
    } senao {
        retorne n * fatorial(n - 1);
    }
}

inicio() {
    inteiro num;
    inteiro res;
    
    exibir("Digite um numero para calcular o fatorial:");
    ler(num);
    
    res = fatorial(num);
    
    exibir("O fatorial eh:");
    exibir(res);
}