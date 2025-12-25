funcao vazio verificar_status(real temp) {
    se (temp >= 40.0) {
        exibir("ALERTA: Superaquecimento!");
    } senao {
        se (temp < 10.0) {
            exibir("ALERTA: Temperatura muito baixa!");
        } senao {
            exibir("Temperatura normal.");
        }
    }
}

funcao real ajustar_sensor(real valor, real fator) {
    retorne valor * fator;
}

inicio() {
    exibir("--- Sistema de Monitoramento V1.5 ---");
    
    real temperatura = 25.0;
    real fator_correcao = 1.2;
    inteiro contador = 0;

    exibir("Iniciando loop de aquecimento...");

    enquanto (contador < 5) {
        exibir("Leitura atual:");
        exibir(temperatura);
        
        verificar_status(temperatura);
        
        // Simulando aumento de temperatura
        temperatura = ajustar_sensor(temperatura, fator_correcao);
        contador = contador + 1;
    }

    exibir("Monitoramento finalizado.");
}