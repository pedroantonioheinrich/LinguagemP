// Definição de Registro
registro Usuario {
    inteiro id;
    real saldo;
    logico ativo;
}

// Testando a função com ponteiro e o novo operador ->
funcao vazio atualizar_saldo(Usuario *u, real valor) {
    // TESTE 1: Usando o novo açúcar sintático ->
    u->saldo = u->saldo + valor;
    
    // TESTE 2: Usando a forma antiga para garantir retrocompatibilidade
    (*u).id = 10; 
}

inicio() {
    // 1. Teste de Ponteiros Básicos
    inteiro x = 500;
    inteiro *ptr = &x;
    *ptr = 1000;
    exibir("Valor de x via ponteiro (1000):");
    exibir(x);

    // 2. Teste de Registros
    Usuario user1;
    user1.id = 1;
    user1.saldo = 150.50;
    user1.ativo = verdadeiro;

    // 3. Chamada de função passando referência
    atualizar_saldo(&user1, 50.0);

    exibir("Novo Saldo (deve ser 200.5):");
    exibir(user1.saldo);
    
    exibir("Novo ID (deve ser 10):");
    exibir(user1.id);
}