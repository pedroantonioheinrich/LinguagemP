inicio() {
    // --- SEÇÃO 1: ARITMÉTICA BÁSICA E NEGATIVOS (1-10) ---
    inteiro a; 
    a = 10;
    exibir(a);               // T1: 10
    a = -5;
    exibir(a);               // T2: -5
    a = 10 + -3;
    exibir(a);               // T3: 7
    a = -10 - -5;
    exibir(a);               // T4: -5
    a = 5 * -2;
    exibir(a);               // T5: -10
    a = -20 / 4;
    exibir(a);               // T6: -5
    a = 10 % 3;
    exibir(a);               // T7: 1 (Resto)
    a = 10 % 2;
    exibir(a);               // T8: 0
    a = -10 % 3;
    exibir(a);               // T9: -1
    inteiro b;
    b = (2 + 3) * -4;
    exibir(b);               // T10: -20

    // --- SEÇÃO 2: INCREMENTO E DECREMENTO (11-20) ---
    inteiro i;
    i = 0;
    i++; 
    exibir(i);               // T11: 1
    i++; 
    exibir(i);               // T12: 2
    i--; 
    exibir(i);               // T13: 1
    i--; 
    exibir(i);               // T14: 0
    
    inteiro j;
    j = -5;
    j++;
    exibir(j);               // T15: -4
    j--;
    exibir(j);               // T16: -5

    // Teste de incremento dentro de loop
    inteiro c;
    c = 0;
    enquanto (c < 3) {
        c++;
    }
    exibir(c);               // T17: 3

    // --- SEÇÃO 3: ATRIBUIÇÃO COMPOSTA (21-30) ---
    inteiro x;
    x = 10;
    x += 5;
    exibir(x);               // T21: 15
    x -= 3;
    exibir(x);               // T22: 12
    x *= 2;
    exibir(x);               // T23: 24
    x /= 4;
    exibir(x);               // T24: 6
    x %= 4;
    exibir(x);               // T25: 2
    
    real f;
    f = 10.5;
    f += 4.5;
    exibir(f);               // T26: 15.0
    f *= 2.0;
    exibir(f);               // T27: 30.0
    f -= 10.0;
    exibir(f);               // T28: 20.0
    f /= 2.0;
    exibir(f);               // T29: 10.0

    // --- SEÇÃO 4: LÓGICA E MATEMÁTICA MISTA (31-40) ---
    inteiro res;
    res = (10 > 5) e (2 < 4);
    exibir(res);              // T31: 1
    
    res = nao (10 == 10);
    exibir(res);              // T32: 0

    inteiro n;
    n = 10;
    se (n % 2 == 0) {
        exibir(100);          // T33: 100 (Par)
    }

    n = 7;
    escolha (n % 2) {
        caso 0:
            exibir(0);
        caso 1:
            exibir(1);        // T34: 1 (Ímpar)
    }

    // Operações complexas aninhadas
    inteiro calc;
    calc = (10 + 5) - (2 * 3); // C aceita isso, vamos ver no nosso
    // Nota: Na Linguagem P, atribuições são comandos. Vamos testar isolado:
    inteiro k;
    k = 10;
    k += (5 * 2);
    exibir(k);                // T35: 20

    inteiro z;
    z -= (10 % 3);
    exibir(z);                // T36: 19

    // Teste de múltiplos incrementos
    inteiro m;
    m = 100;
    m++; m++; m--;
    exibir(m);                // T37: 101

    // Teste de sinal negativo em variável
    inteiro p;
    p = 50;
    exibir(-p);               // T38: -50

    // Teste de zero e negativo no resto
    exibir(0 % 5);            // T39: 0

    // Teste Final: Tudo junto
    inteiro total;
    total = 0;
    total += 10;
    total *= 2;
    total--;
    exibir(total);            // T40: 19
}