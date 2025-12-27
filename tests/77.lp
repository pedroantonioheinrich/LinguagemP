registro Sensor {
    inteiro pino;
    logico ativo;
}

inicio() {
    Sensor porta;
    porta.pino = 5;
    porta.ativo = verdadeiro;

    exibir("--- Teste de Automacao ---");
    
    se (porta.ativo) {
        exibir("Status: Porta Aberta!");
        ligar(porta.pino);
        exibir("Acao: Alarme ligado no pino 5");
    } senao {
        exibir("Status: Porta Fechada.");
        desligar(porta.pino);
    }
}