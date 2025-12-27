// ==========================================
// BATERIA DE TESTES MASSIVOS - LINGUAGEM P
// COBERTURA: T1 - T80
// ==========================================

registro Pessoa {
    inteiro id;
    real altura;
    inteiro idade;
}

registro Item {
    inteiro codigo;
    real preco;
}

funcao vazio trocar(inteiro* a, inteiro* b) {
    inteiro temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

funcao inteiro soma(inteiro x, inteiro y) {
    retorno x + y;
}

funcao real area_circulo(real raio) {
    retorno 3.14 * raio * raio;
}

funcao vazio dobrar_reg(Pessoa* p) {
    *p.idade = *p.idade * 2;
}

inicio() {
    // --- BÁSICOS (T1-T10) ---
    inteiro a; a = 10;
    inteiro b; b = 20;
    exibir("T1 - Soma Simples:"); exibir(a + b);
    exibir("T2 - Subtracao:"); exibir(b - a);
    exibir("T3 - Multiplicacao:"); exibir(a * b);
    exibir("T4 - Divisao:"); exibir(b / a);
    exibir("T5 - Expressao Complexa:"); exibir((a + b) * 2 / 3);
    real r1; r1 = 10.5;
    real r2; r2 = 2.0;
    exibir("T6 - Real Soma:"); exibir(r1 + r2);
    exibir("T7 - Real Divisao:"); exibir(r1 / r2);
    inteiro neg; neg = -50;
    exibir("T8 - Negativos:"); exibir(neg + 100);
    exibir("T9 - Modulo (simulado):"); exibir(10 - 3);
    exibir("T10 - Atribuicao Multipla:"); a = b; exibir(a);

    // --- CONDICIONAIS E LAÇOS (T11-T20) ---
    exibir("T11 - Se Verdadeiro:");
    se (a == 20) { exibir(1); }
    exibir("T12 - Se Falso:");
    se (a < 10) { exibir(0); }
    exibir("T13 - Enquanto decremento:");
    inteiro contador; contador = 3;
    enquanto (contador > 0) {
        exibir(contador);
        contador = contador - 1;
    }
    exibir("T14 - Se encadeado:");
    se (1 > 0) { se (2 > 1) { exibir(200); } }

    // --- PONTEIROS BÁSICOS (T21-T35) ---
    inteiro x; x = 100;
    inteiro* ptr; ptr = &x;
    exibir("T21 - Endereco/Referencia:"); exibir(*ptr);
    *ptr = 150;
    exibir("T22 - Alteracao via ponteiro:"); exibir(x);
    inteiro** pptr; pptr = &ptr;
    exibir("T23 - Ponteiro Duplo:"); exibir(**pptr);
    **pptr = 300;
    exibir("T24 - Alteracao via ponteiro duplo:"); exibir(x);
    inteiro* p2; p2 = &b;
    exibir("T25 - Soma de valores apontados:"); exibir(*ptr + *p2);
    exibir("T26 - Ponteiro e Constante:"); exibir(*ptr + 50);
    exibir("T27 - Multiplicacao com Ponteiro:"); exibir(*ptr * 2);
    exibir("T28 - Ponteiro para Ponteiro soma:"); exibir(**pptr + 100);
    *&x = 500;
    exibir("T29 - Desreferencia imediata *&:"); exibir(x);
    inteiro* p_nulo; // Teste de declaracao
    exibir("T30 - Ponteiro p2 original:"); exibir(*p2);

    // --- FUNÇÕES E PARÂMETROS (T36-T50) ---
    exibir("T36 - Chamada Funcao Soma:"); exibir(soma(5, 5));
    inteiro n1; n1 = 1;
    inteiro n2; n2 = 9;
    trocar(&n1, &n2);
    exibir("T37 - Troca via ponteiro n1:"); exibir(n1);
    exibir("T38 - Troca via ponteiro n2:"); exibir(n2);
    exibir("T39 - Area Circulo (Real):"); exibir(area_circulo(2.0));
    exibir("T40 - Funcao com expressao:"); exibir(soma(a*2, b));

    // --- REGISTROS (T51-T65) ---
    Pessoa p_teste;
    p_teste.id = 1;
    p_teste.idade = 25;
    p_teste.altura = 1.75;
    exibir("T51 - Registro Campo Int:"); exibir(p_teste.id);
    exibir("T52 - Registro Campo Real:"); exibir(p_teste.altura);
    Pessoa* ptr_p; ptr_p = &p_teste;
    exibir("T53 - Registro via Ponteiro:"); exibir(*ptr_p.idade);
    *ptr_p.idade = 30;
    exibir("T54 - Alterar campo via ponteiro:"); exibir(p_teste.idade);
    dobrar_reg(&p_teste);
    exibir("T55 - Funcao alterando registro:"); exibir(p_teste.idade);
    Item it; it.codigo = 999; it.preco = 49.90;
    exibir("T56 - Segundo Registro:"); exibir(it.preco);
    
    // --- ESCOPO E SHADOWING (T66-T75) ---
    inteiro escopo; escopo = 10;
    {
        inteiro escopo; escopo = 20;
        exibir("T66 - Shadowing Interno:"); exibir(escopo);
    }
    exibir("T67 - Escopo Original:"); exibir(escopo);

    // --- TESTES DE LIMITE E SINTAXE (T76-T80) ---
    inteiro val; val = (10 + (20 * (30 / 10)));
    exibir("T76 - Parenteses aninhados:"); exibir(val);
    inteiro* p_final; p_final = &val;
    exibir("T77 - Ponteiro de expressao:"); exibir(*p_final + 1);
    exibir("T78 - Fim de bateria...");
    exibir("T79 - Teste Real em Expressao:"); exibir(10.0 / 4.0);
    exibir("T80 - Ultimo Teste:"); exibir(80);
}