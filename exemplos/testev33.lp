inicio() {
    // --- SEÇÃO 1: MATRIZES UNIDIMENSIONAIS (VETORES) (1-10) ---
    inteiro v[5];
    v[0] = 10;
    v[1] = 20;
    v[2] = v[0] + v[1];
    exibir(v[0]);               // T1: 10
    exibir(v[2]);               // T2: 30
    
    real precos[3];
    precos[0] = 1.5;
    precos[1] = 2.5;
    exibir(precos[0] + precos[1]); // T3: 4.0
    
    inteiro i;
    para (i de 0 ate 3) {
        v[i] = i * 10;
    }
    exibir(v[2]);               // T4: 20

    // --- SEÇÃO 2: MATRIZES MULTIDIMENSIONAIS (11-20) ---
    inteiro matriz[2][2];
    matriz[0][0] = 1;
    matriz[0][1] = 2;
    matriz[1][0] = 3;
    matriz[1][1] = 4;
    exibir(matriz[0][0]);       // T11: 1
    exibir(matriz[1][1]);       // T12: 4
    
    inteiro soma;
    soma = matriz[0][0] + matriz[1][1];
    exibir(soma);               // T13: 5
    
    matriz[0][0]++;
    exibir(matriz[0][0]);       // T14: 2

    // Matriz 3D (se o seu sintático suportar múltiplos colchetes)
    inteiro cubo[2][2][2];
    cubo[1][1][1] = 99;
    exibir(cubo[1][1][1]);      // T15: 99

    // --- SEÇÃO 3: CADEIAS DE TEXTO (STRINGS) (21-30) ---
    cadeia nome;
    nome = "Pedro";
    exibir(nome);               // T21: Pedro

    cadeia sobrenome;
    sobrenome = "Silva";
    exibir(sobrenome);          // T22: Silva

    // Teste de strcpy via atribuição
    cadeia copia;
    copia = nome;
    exibir(copia);              // T23: Pedro

    // Vetor de Strings
    cadeia lista[2];
    lista[0] = "Linguagem";
    lista[1] = "P";
    exibir(lista[0]);           // T24: Linguagem
    exibir(lista[1]);           // T25: P

    // Strings dentro de Matrizes
    cadeia tabela[2][2];
    tabela[0][0] = "A1";
    tabela[1][1] = "B2";
    exibir(tabela[0][0]);       // T26: A1
    exibir(tabela[1][1]);       // T27: B2

    // --- SEÇÃO 4: INTEGRAÇÃO REGISTRO + MATRIZ ---
    // (Assumindo que o registro foi declarado fora ou antes)
    // Se o seu compilador exigir declaração global, mova para fora do inicio()
    
    // Teste de leitura de string com espaço
    // exibir("Digite seu nome completo:");
    // leia(nome); 
    // exibir(nome);            // T28: (Validar entrada manual)

    inteiro final;
    final = 100;
    v[0] = final;
    exibir(v[0]);               // T29: 100

    exibir("Fim dos Testes");   // T30
}