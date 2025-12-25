inicio() {
    inteiro LED = 13;
    
    exibir("Iniciando Monitoramento...");

    sempre {
        inteiro botao = ler(2);
        
        se (botao == 1) {
            ligar(LED);
            exibir("Status: ATIVO");
        } senao {
            desligar(LED);
        }
        
        esperar(500); # Verifica a cada meio segundo
    }
    
    retorne 0;
}