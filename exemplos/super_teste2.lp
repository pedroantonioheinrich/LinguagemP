registro Produto {
    cadeia nome;
    real preco;
}

inicio() {
    // 1. Teste de Variáveis e Leia
    cadeia usuario;
    inteiro idade;
    real altura;
    
    exibir("--- TESTE 1: ENTRADA DE DADOS ---");
    exibir("Digite seu nome:");
    leia(usuario);
    exibir("Digite sua idade:");
    leia(idade);
    
    // 2. Teste de Se/Senao e Lógica
    exibir("--- TESTE 2: DECISAO ---");
    se (idade >= 18) {
        exibir("Voce e maior de idade.");
    } senao {
        exibir("Voce e menor de idade.");
    }

    // 3. Teste de Matemática Complexa
    inteiro a;
    inteiro b;
    inteiro calculo;
    
    a = 10;
    b = 5;
    calculo = (a + b) * 2 / 5; // Deve resultar em 6
    
    exibir("--- TESTE 3: MATEMATICA ---");
    exibir("O resultado de (10+5)*2/5 deve ser 6. Calculado:");
    exibir(calculo);

    // 4. Teste de Registro e Atribuição
    Produto p1;
    exibir("--- TESTE 4: REGISTROS ---");
    p1.nome = "Teclado";
    p1.preco = 150.50;
    exibir(p1.nome);
    exibir(p1.preco);

    // 5. Teste de Loop Para
    inteiro i;
    exibir("--- TESTE 5: LOOP PARA ---");
    para (i de 1 ate 4) {
        exibir("Repeticao numero:");
        exibir(i);
    }

    exibir("--- FIM DOS TESTES ---");
}