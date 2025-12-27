inicio() {
    inteiro pino = 13;
    inteiro contador = 0;
    inteiro limite = 0;
    
    exibir("Quantas vezes o LED deve piscar?");
    limite = ler();
    
    enquanto (contador < limite) {
        exibir("Piscando...");
        ligar(pino);
        esperar(500);
        desligar(pino);
        esperar(500);
        
        contador = contador + 1;
    }
    
    exibir("Ciclo de automacao finalizado.");
    retorne 0;
}