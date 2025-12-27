registro Produto {
    cadeia nome;
    real preco;
}

funcao real aplicar_desconto(real valor, real taxa) {
    retorno valor * (1.0 - taxa);
}

inicio() {
    // 1. Teste de Vetores Primitivos
    inteiro notas[3];
    notas[0] = 10;
    notas[1] = 8;
    notas[2] = 9;

    exibir("--- TESTE 1: VETORES ---");
    exibir("Nota 1:");
    exibir(notas[0]);

    // 2. Teste de Registros
    Produto p1;
    p1.nome = "Monitor";
    p1.preco = 1200.0;

    exibir("--- TESTE 2: REGISTROS E FUNCOES ---");
    exibir("Produto:");
    exibir(p1.nome);
    exibir("Preco original:");
    exibir(p1.preco);

    // 3. Teste de Chamada de Função com Retorno
    real preco_final;
    preco_final = aplicar_desconto(p1.preco, 0.10); // 10% de desconto
    
    exibir("Preco com 10% de desconto:");
    exibir(preco_final);

    // 4. Teste de Loop Enquanto com Vetor
    exibir("--- TESTE 3: LOOP COM VETOR ---");
    inteiro i;
    i = 0;
    enquanto (i < 3) {
        exibir("Lendo nota do indice:");
        exibir(i);
        exibir(notas[i]);
        i = i + 1;
    }
}