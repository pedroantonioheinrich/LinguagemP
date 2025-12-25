inicio() {
    /* Comentário de múltiplas linhas:
       Testando Hardware e Tempo 
    */
    inteiro LED = 13;
    
    exibir("Iniciando Sequencia de Hardware...");
    
    ligar(LED);
    esperar(1000); # Aguarda 1 segundo
    desligar(LED);
    
    exibir("Fim do Ciclo.");
    retorne 0;
}