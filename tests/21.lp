funcao inteiro eh_par(inteiro n) {
    se (n == (n / 2) * 2) {
        retorne 1;
    }
    retorne 0;
}

inicio() {
    exibir("10 eh par? (1-Sim, 0-Nao):");
    exibir(eh_par(10));
    exibir("7 eh par? (1-Sim, 0-Nao):");
    exibir(eh_par(7));
}