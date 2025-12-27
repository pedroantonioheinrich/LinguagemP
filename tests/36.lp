funcao contar_ate_tres() {
    inteiro i;
    para (i = 1; i <= 3; i = i + 1) {
        exibir(i);
    }
}

inicio() {
    inteiro i;
    para (i = 1; i <= 2; i = i + 1) {
        exibir("Loop principal:");
        contar_ate_tres();
    }
}