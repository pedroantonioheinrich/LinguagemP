registro Aluno {
    cadeia nome;
    real nota;
}

inicio() {
    // Matriz de Registros
    Aluno turma[2];
    
    turma[0].nome = "Pedro";
    turma[0].nota = 9.5;
    
    turma[1].nome = "Linguagem P";
    turma[1].nota = 10.0;

    // Operadores Incrementais
    inteiro i = 0;
    exibir("--- Alunos ---");
    enquanto (i < 2) {
        exibir(turma[i].nome);
        exibir(turma[i].nota);
        i++; // O novo operador incremental!
    }

    inteiro x = 10;
    x--;
    exibir("--- Teste Decremento ---");
    exibir(x); // Deve exibir 9
}