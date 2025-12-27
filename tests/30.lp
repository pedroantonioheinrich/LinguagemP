inicio() {
    inteiro cooler = 13;
    real temperatura = 0.0;
    
    exibir("Digite a temperatura atual:");
    temperatura = ler();
    
    se (temperatura > 30.0) {
        exibir("ALERTA: Superaquecimento!");
        ligar(cooler);
    } senao {
        exibir("Temperatura normal.");
        desligar(cooler);
    }
    
    retorne 0;
}