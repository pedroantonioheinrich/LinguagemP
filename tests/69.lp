// Teste Definitivo Linguagem P - V30.0
// Matrizes + Operadores Lógicos + Registros

registro Jogador {
    inteiro id;
    inteiro pontos;
}

inicio() {
    inteiro mapa[3][3];
    inteiro i;
    inteiro j;
    inteiro nivel;
    Jogador p1;

    p1.id = 1;
    p1.pontos = 100;
    nivel = 2;

    exibir("--- Iniciando Teste de Logica Composta ---");

    // Preenchendo a matriz com lógica
    para (i de 0 ate 3) {
        para (j de 0 ate 3) {
            mapa[i][j] = i + j;
        }
    }

    // TESTE 1: Matriz + Operador Lógico 'e'
    se (mapa[1][1] == 2 e p1.pontos >= 100) {
        exibir("Teste 1: Sucesso - Matriz e Pontos validados com 'e'");
    } senao {
        exibir("Teste 1: Falha");
    }

    // TESTE 2: Operador Lógico 'ou' + Variáveis
    se (nivel == 1 ou p1.id == 1) {
        exibir("Teste 2: Sucesso - Identificador validado com 'ou'");
    }

    // TESTE 3: Expressão complexa no Exibir
    exibir("Resultado da expressao logica direta (deve ser 1):");
    exibir(mapa[2][2] > 0 e nivel < 5);

    // TESTE 4: Matriz Bidimensional na borda
    inteiro valor_final;
    valor_final = mapa[2][2];
    se (valor_final == 4 e (nivel == 2 ou p1.id == 0)) {
        exibir("Teste 4: Sucesso - Logica aninhada e Matriz");
    }

    exibir("--- Fim dos Testes V30.0 ---");
}