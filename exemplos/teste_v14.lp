funcao real calcular_media(real n1, real n2) {
    retorne (n1 + n2) / 2;
}

funcao void aviso_fim() {
    exibir("Programa finalizado.");
}

inicio() {
    real m = calcular_media(10.5, 7.5);
    exibir(m);
    aviso_fim();
}