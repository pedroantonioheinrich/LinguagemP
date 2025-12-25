funcao piscar(pino, tempo) {
    ligar(pino);
    esperar(tempo);
    desligar(pino);
    esperar(tempo);
}

inicio() {
    inteiro LED = 13;
    exibir("Iniciando sequencia de pisca...");
    
    piscar(LED, 200);
    piscar(LED, 200);
    
    exibir("Sequencia concluida.");
    retorne 0;
}