inicio() {
    inteiro sensor = 1;
    inteiro luminosidade = 5;
    
    se (sensor == 1 e luminosidade < 10) {
        exibir("Ambiente escuro com presenca. Ligando luz...");
        ligar(13);
    } senao {
        exibir("Condicoes nao atendidas.");
    }
    
    retorne 0;
}