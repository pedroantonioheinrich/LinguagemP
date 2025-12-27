funcao real calcular_dobro(real n) {
    retorne n * 2;
}

inicio() {
    real x;
    exibir("Digite um numero para dobrar:");
    ler(x);
    
    real resultado = calcular_dobro(x);
    
    exibir("O dobro e:");
    exibir(resultado);
}