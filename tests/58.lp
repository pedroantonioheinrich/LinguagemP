funcao inteiro calcular_dobro(inteiro n) {
    retorne n * 2;
}

inicio() {
    exibir("Digite um numero:");
    inteiro valor = ler();
    inteiro resultado = calcular_dobro(valor);
    exibir("O dobro e:");
    exibir(resultado);
}