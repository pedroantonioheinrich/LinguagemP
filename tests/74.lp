registro Aluno {
    inteiro notas[3];
}

inicio() {
    Aluno p;
    p.notas[0] = 7;
    p.notas[1] = 8;
    p.notas[2] = 9;
    
    real media = (p.notas[0] + p.notas[1] + p.notas[2]) / 3;
    exibir("A media do aluno e:");
    exibir(media);
}