funcao real calcular_area(real base, real altura) {
    retorne base * altura;
}

funcao saudacao() {
    exibir("Bem-vindo ao sistema de calculo!");
}

inicio() {
    saudacao();
    
    real b;
    real a;
    real resultado;
    
    exibir("Digite a base:");
    ler(b);
    exibir("Digite a altura:");
    ler(a);
    
    resultado = calcular_area(b, a);
    
    exibir("A area do retangulo eh:");
    exibir(resultado);
}