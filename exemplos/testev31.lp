// Teste de Fogo Linguagem P - V31.0
// Validando: nao, e, ou, Matrizes e Registros

registro Sistema {
    inteiro status;
    inteiro erro_critico;
}

inicio() {
    inteiro matriz[2][2];
    Sistema sys;
    inteiro x;

    // Inicialização
    sys.status = 1;
    sys.erro_critico = 0;
    matriz[0][0] = 10;
    matriz[1][1] = 20;
    x = 50;

    exibir("--- Iniciando Suite de Testes V31.0 ---");

    // TESTE 1: Negação simples
    se (nao (sys.erro_critico == 1)) {
        exibir("Teste 1: Sucesso - Negação de igualdade");
    }

    // TESTE 2: Negação com lógica composta (e/ou)
    se (nao (sys.status == 0) e x > 40) {
        exibir("Teste 2: Sucesso - NAO combinado com E");
    }

    // TESTE 3: Matriz + NAO + OU
    se (nao (matriz[0][0] == 0) ou matriz[1][1] == 100) {
        exibir("Teste 3: Sucesso - Matriz validada com negação");
    }

    // TESTE 4: Expressão booleana aninhada no Exibir
    exibir("Resultado logico complexo (deve ser 1):");
    exibir(nao (x < 10) e (sys.status == 1));

    // TESTE 5: Verificação de segurança (Lógica Inversa)
    se (nao (sys.erro_critico == 1 ou x == 0)) {
        exibir("Teste 5: Sucesso - Seguranca validada (NAO OU)");
    }

    exibir("--- Fim dos Testes V31.0 ---");
}