inteiro notas[3];

// Adicione "real" ou "inteiro" aqui:
funcao real calcular_media() {
    retorne (notas[0] + notas[1] + notas[2]) / 3;
}

inicio() {
    notas[0] = 10;
    notas[1] = 8;
    notas[2] = 6;
    exibir("Media (deve ser 8):");
    exibir(calcular_media());
}