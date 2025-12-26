inicio() {
    inteiro i;
    inteiro numeros[5];

    exibir("Preenchendo vetor...");
    para (i de 0 ate 4) {
        numeros[i] = i * 10;
    }

    exibir("Valores no vetor:");
    para (i de 0 ate 4) {
        exibir(numeros[i]);
    }
}