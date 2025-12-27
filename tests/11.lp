registro Aluno {
    cadeia nome;
    real nota;
}

inicio() {
    Aluno p;
    inteiro i;
    
    p.nome = "Pedro";
    p.nota = 10.0;

    exibir("Dados do Aluno:");
    exibir(p.nome);
    exibir(p.nota);

    exibir("Contagem de verificacao:");
    para (i de 1 ate 4) {
        exibir(i);
    }
}