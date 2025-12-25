inicio() {
    exibir("--- Teste Versão 1.1 ---");
    
    // Teste de Atribuição Composta
    inteiro x = 10;
    x += 5;
    exibir("X deve ser 15:");
    exibir(x);
    
    // Teste do Laço Para
    exibir("Contagem com PARA:");
    para (inteiro i = 1; i <= 5; i += 1) {
        exibir(i);
        ligar(13);
        esperar(100);
        desligar(13);
    }
}