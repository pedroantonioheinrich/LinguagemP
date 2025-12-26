registro Aluno {
    inteiro notas[3];
}

inicio() {
    Aluno p;
    inteiro i;
    real soma = 0;

    exibir("Digite as 3 notas do aluno:");
    
    para (i = 0; i < 3; i = i + 1) {
        ler(p.notas[i]);
    }
    
    para (i = 0; i < 3; i = i + 1) {
        soma = soma + p.notas[i];
    }
    
    real media = soma / 3;
    exibir("A media final e:");
    exibir(media);
}