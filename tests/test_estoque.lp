registro Produto {
    cadeia nome;
    real preco;
    inteiro qtd;
}

// Funcao para processar o valor total
funcao real calcular(Produto p) {
    retorne p.preco * p.qtd;
}

inicio() {
    Produto lista[2];
    real totalGeral = 0.0;

    lista[0].nome = "Teclado";
    lista[0].preco = 100.0;
    lista[0].qtd = 2;

    lista[1].nome = "Mouse";
    lista[1].preco = 50.0;
    lista[1].qtd = 5;

    exibir("--- Relatorio de Estoque ---");
    
    inteiro i;
    para (i de 0 ate 1) {
        real subtotal = calcular(lista[i]);
        totalGeral = totalGeral + subtotal;
        exibir(lista[i].nome);
        exibir("Subtotal:");
        exibir(subtotal);
    }

    exibir("Total Geral:");
    exibir(totalGeral);
}