inicio() {
    inteiro mat[3][3];
    inteiro i;
    inteiro j;

    para (i = 0; i < 3; i = i + 1) {
        para (j = 0; j < 3; j = j + 1) {
            se (i == j) {
                mat[i][j] = 1;
            } senao {
                mat[i][j] = 0;
            }
        }
    }

    exibir("Matriz Identidade:");
    para (i = 0; i < 3; i = i + 1) {
        exibir(mat[i][0]);
        exibir(mat[i][1]);
        exibir(mat[i][2]);
    }
}