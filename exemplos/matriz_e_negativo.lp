inicio() {
    // Teste de Negativos
    inteiro saldo = -50;
    real temperatura = -10.5;
    
    exibir("--- Negativos ---");
    exibir(saldo);
    exibir(temperatura);

    // Teste de Array de Inteiros
    inteiro notas[3];
    notas[0] = 10;
    notas[1] = -5;
    notas[2] = 8;

    exibir("--- Array ---");
    exibir(notas[1]);

    // Teste de Matriz (2D)
    inteiro matriz[2][2];
    matriz[0][0] = 1;
    matriz[1][1] = -99;

    exibir("--- Matriz ---");
    exibir(matriz[1][1]);
}