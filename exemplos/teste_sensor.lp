inicio() {
    inteiro botao = ler(2);
    inteiro LED = 13;

    se (botao == 1) {
        exibir("Botao pressionado! Ligando LED...");
        ligar(LED);
    } senao {
        exibir("Aguardando...");
        desligar(LED);
    }

    retorne 0;
}