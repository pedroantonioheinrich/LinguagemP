inicio() {
    inteiro contador;
    contador = 0;

    exibir("--- TESTE DO LOOP ENQUANTO ---");

    enquanto (contador < 5) {
        exibir("Contagem atual:");
        exibir(contador);
        contador = contador + 1;
    }

    exibir("Fim do loop!");
}