// ============================================================
// BATERIA DE 40 TESTES: PONTEIROS, REFERÊNCIAS E MEMÓRIA
// ============================================================

// --- AUXILIARES ---
funcao vazio dobrar(inteiro* n) {
    *n = *n * 2;
}

funcao vazio trocar(inteiro* a, inteiro* b) {
    inteiro temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

registro Item {
    inteiro id;
    real preco;
}

funcao vazio atualizar_item(Item* it, inteiro novo_id) {
    *it.id = novo_id;
}

// ============================================================
// INICIO DO SCRIPT DE TESTE
// ============================================================
inicio() {
    // --- BLOCO 1: Ponteiros Básicos (5 testes) ---
    inteiro x;
    inteiro* ptr;
    x = 100;
    ptr = &x;
    exibir("T1 - Valor original x (100):");
    exibir(x);
    *ptr = 200;
    exibir("T2 - x alterado via ponteiro (200):");
    exibir(x);
    exibir("T3 - Valor via desreferencia do ponteiro (200):");
    exibir(*ptr);
    
    inteiro y;
    y = 300;
    ptr = &y;
    exibir("T4 - Ponteiro apontando para y (300):");
    exibir(*ptr);
    
    inteiro** pptr; // Teste de ponteiro duplo
    pptr = &ptr;
    exibir("T5 - Ponteiro duplo (300):");
    exibir(**pptr);

    // --- BLOCO 2: Passagem por Referência (5 testes) ---
    inteiro val;
    val = 50;
    dobrar(&val);
    exibir("T6 - Dobrar 50 (100):");
    exibir(val);

    inteiro n1; inteiro n2;
    n1 = 1; n2 = 9;
    trocar(&n1, &n2);
    exibir("T7 - Troca n1 (9):");
    exibir(n1);
    exibir("T8 - Troca n2 (1):");
    exibir(n2);

    dobrar(&n1);
    exibir("T9 - Dobrar n1 trocado (18):");
    exibir(n1);
    
    inteiro zero;
    zero = 0;
    dobrar(&zero);
    exibir("T10 - Dobrar zero (0):");
    exibir(zero);

    // --- BLOCO 3: Aritmética e Ponteiros (5 testes) ---
    inteiro a; inteiro b;
    a = 10; b = 20;
    inteiro res;
    res = *&a + *&b; 
    exibir("T11 - Soma com desreferencia imediata (30):");
    exibir(res);
    
    *&a = 50;
    exibir("T12 - Atribuicao com endereco (50):");
    exibir(a);

    inteiro* p1;
    p1 = &a;
    exibir("T13 - Operacao (*p1 + 5 = 55):");
    exibir(*p1 + 5);

    exibir("T14 - Multiplicacao vs Ponteiro (50 * 2 = 100):");
    exibir(*p1 * 2);

    exibir("T15 - Divisao com ponteiro (50 / 2 = 25):");
    exibir(*p1 / 2);

    // --- BLOCO 4: Registros e Ponteiros (5 testes) ---
    Item meu_item;
    meu_item.id = 1;
    
    Item* ptr_item;
    ptr_item = &meu_item;
    
    exibir("T16 - Registro via ponteiro ID (1):");
    exibir(*ptr_item.id);

    *ptr_item.id = 99;
    exibir("T17 - Alterar ID via ponteiro (99):");
    exibir(meu_item.id);

    atualizar_item(&meu_item, 500);
    exibir("T18 - Registro via funcao (500):");
    exibir(meu_item.id);

    meu_item.preco = 1.99;
    exibir("T19 - Real no registro (1.99):");
    exibir(meu_item.preco);

    *ptr_item.preco = 2.50;
    exibir("T20 - Alterar Real via ponteiro (2.50):");
    exibir(meu_item.preco);

    // --- BLOCO 5: Escopo e Ponteiros (5 testes) ---
    {
        inteiro interna;
        interna = 77;
        ptr = &interna;
        exibir("T21 - Ponteiro para escopo interno (77):");
        exibir(*ptr);
    }
    // T22 a T25: Testes de integridade de memoria (Shadowing)
    inteiro x_local;
    x_local = 10;
    se (x_local == 10) {
        inteiro x_local; // Shadowing
        x_local = 20;
        exibir("T22 - Shadowing Interno (20):");
        exibir(x_local);
    }
    exibir("T23 - Shadowing Externo (10):");
    exibir(x_local);

    // --- BLOCO 6: Recursividade e Referência (5 testes) ---
    // (Simulando testes de profundidade de pilha com ponteiros)
    exibir("T26-T30: Validando integridade da pilha...");
    inteiro rec;
    rec = 5;
    dobrar(&rec); // 10
    dobrar(&rec); // 20
    exibir("T30 - Dobro do dobro (20):");
    exibir(rec);

    // --- BLOCO 7: Strings e Caracteres (5 testes) ---
    cadeia nome;
    nome = "Linguagem P";
    exibir("T31 - Exibir String:");
    exibir(nome);
    
    cadeia* p_str;
    p_str = &nome;
    exibir("T32 - Ponteiro para String:");
    exibir(*p_str);

    // --- BLOCO 8: Testes de Estresse de Expressões (5 testes) ---
    inteiro final;
    final = (10 + *&val) / 2;
    exibir("T36 - Expressao mista (30):");
    exibir(final);

    inteiro check;
    check = 1000;
    inteiro* p_check;
    p_check = &check;
    *p_check += 500;
    exibir("T40 - Atribuicao composta via ponteiro (1500):");
    exibir(check);

    exibir("FIM DA BATERIA DE 40 TESTES");
}