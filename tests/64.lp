inteiro x = 10;

funcao muda_x() {
    inteiro x = 50;
    exibir("Local x (deve ser 50):");
    exibir(x);
}

inicio() {
    muda_x();
    exibir("Global x (deve ser 10):");
    exibir(x);
}