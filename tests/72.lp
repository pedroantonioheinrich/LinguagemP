// Definição de Estruturas Complexas
registro Usuario {
    inteiro id;
    cadeia apelido;      // Teste: nome que não contém "nome" ou "texto"
    real saldo;
}

registro Empresa {
    cadeia razao_social;
    inteiro funcionarios;
}

inicio() {
    // 1. Teste de Tipos Primitivos
    inteiro contador = 100;
    cadeia saudacao = "Bem-vindo ao sistema P";
    real pi = 3.1415;

    // 2. Instanciação de Registros
    Usuario u;
    Empresa e;

    // 3. Atribuição de Valores
    u.id = 1;
    u.apelido = "dev_pedro";
    u.saldo = 1550.75;

    e.razao_social = "Tech Solutions P";
    e.funcionarios = 50;

    // 4. Teste de Exibição com Semântica Forte
    exibir(saudacao);
    
    exibir("--- Dados do Usuario ---");
    exibir(u.id);        // Deve gerar %g
    exibir(u.apelido);   // Deve gerar %s (Mesmo sem a palavra 'nome')
    exibir(u.saldo);     // Deve gerar %g

    exibir("--- Dados da Empresa ---");
    exibir(e.razao_social); // Deve gerar %s
    exibir(e.funcionarios); // Deve gerar %g

    // 5. Teste de Expressão em Variável Simples
    inteiro dobro;
    dobro = contador * 2;
    exibir(dobro);
}