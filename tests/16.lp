inicio() {
    inteiro mat[2][2];
    inteiro i;
    inteiro j;

    exibir("Digite os 4 valores da matriz 2x2:");
    para (i = 0; i < 2; i = i + 1) {
        para (j = 0; j < 2; j = j + 1) {
            ler(mat[i][j]);
        }
    }

    exibir("Voce digitou:");
    para (i = 0; i < 2; i = i + 1) {
        exibir(mat[i][0]);
        exibir(mat[i][1]);
    }
}