// Teste de Matrizes e Registros - Linguagem P V29.0

registro Posicao {
    inteiro x;
    inteiro y;
}

funcao inteiro calcular_soma(inteiro a, inteiro b) {
    retorno a + b;
}

inicio() {
    // 1. Teste de Matriz Bidimensional
    inteiro grade[3][3];
    inteiro i;
    inteiro j;
    inteiro contador;
    contador = 1;

    exibir("--- Inicializando Matriz 3x3 ---");
    
    para (i de 0 ate 3) {
        para (j de 0 ate 3) {
            grade[i][j] = contador;
            contador = contador + 1;
        }
    }

    // 2. Teste de Acesso e Exibição
    exibir("Valor na posicao [1][1]:");
    exibir(grade[1][1]);

    // 3. Teste de Registro com Matriz
    Posicao ponto;
    ponto.x = grade[0][0];
    ponto.y = grade[2][2];

    exibir("Coordenada X do registro:");
    exibir(ponto.x);

    // 4. Teste de Condicional com Matriz
    se (grade[2][2] > 5) {
        exibir("O ultimo elemento eh maior que 5");
    } senao {
        exibir("O ultimo elemento eh pequeno");
    }

    exibir("Teste finalizado com sucesso!");
}