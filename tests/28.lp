 // Este programa testa Constantes, Comentários e Resto de Divisão
inicio() {
    constante inteiro LED = 13;
    inteiro i = 1;
    
    // O loop vai até 10
    enquanto (i <= 10) {
        se (i % 2 == 0) {
            exibir("Numero par detectado:");
            exibir(i);
            ligar(LED);
        } senao {
            desligar(LED);
        }
        i = i + 1;
    }
    
    // LED = 10; // Se você descomentar isso, o compilador deve dar ERRO!
    retorne 0;
}